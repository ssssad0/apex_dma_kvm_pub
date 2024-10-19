#include "memory.h"

// Credits: learn_more, stevemk14ebr
/* size_t findPattern(const PBYTE rangeStart, size_t len, const char *pattern)
{
	size_t l = strlen(pattern);
	PBYTE patt_base = static_cast<PBYTE>(malloc(l >> 1));
	PBYTE msk_base = static_cast<PBYTE>(malloc(l >> 1));
	PBYTE pat = patt_base;
	PBYTE msk = msk_base;
	if (pat && msk)
	{
		l = 0;
		while (*pattern)
		{
			if (*pattern == ' ')
				pattern++;
			if (!*pattern)
				break;
			if (*(PBYTE)pattern == (BYTE)'\?')
			{
				*pat++ = 0;
				*msk++ = '?';
				pattern += ((*(PWORD)pattern == (WORD)'\?\?') ? 2 : 1);
			}
			else
			{
				*pat++ = getByte(pattern);
				*msk++ = 'x';
				pattern += 2;
			}
			l++;
		}
		*msk = 0;
		pat = patt_base;
		msk = msk_base;
		for (size_t n = 0; n < (len - l); ++n)
		{
			if (isMatch(rangeStart + n, patt_base, msk_base))
			{
				free(patt_base);
				free(msk_base);
				return n;
			}
		}
		free(patt_base);
		free(msk_base);
	}
	return -1;
} */

uint64_t Memory::get_proc_baseaddr()
{
	return proc.baseaddr;
}

process_status Memory::get_proc_status()
{
	return status;
}

void Memory::check_proc()
{
	if (status == process_status::FOUND_READY)
	{
		short c;
		Read<short>(proc.baseaddr, c);

		if (c != 0x5A4D)
		{
			status = process_status::FOUND_NO_ACCESS;
			close_proc();
		}
	}
}

bool kernel_init(Inventory *inv, const char *connector_name)
{
	if (inventory_create_connector(inv, connector_name, "", conn.get()))
	{
		printf("Can't create %s connector\n", connector_name);
		return false;
	}
	else
	{
		printf("%s connector created\n", connector_name);
	}

	kernel = std::make_unique<OsInstance<>>();
	if (inventory_create_os(inv, "win32", "", conn.get(), kernel.get()))
	{
		printf("Unable to initialize kernel using %s connector\n", connector_name);
		connector_drop(conn.get());
		kernel.reset();
		return false;
	}

	return true;
}

#include <fstream>
#include <sstream>
#include <string>
#include <set>
const std::string dtb_filename = "valid_dtbs.txt";

void ensure_file_exists(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        // File does not exist, create an empty file
        std::ofstream new_file(filename);
        if (!new_file) {
            printf("Error: Could not create file %s\n", filename.c_str());
            exit(1);
        }
    }
}

std::set<size_t> load_valid_dtbs(const std::string& filename) {
    std::set<size_t> dtb_set;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        size_t dtb;
        if (iss >> dtb) {
            dtb_set.insert(dtb);
        }
    }
    return dtb_set;
}

void append_valid_dtb(const std::string& filename, size_t dtb) {
    std::ofstream file(filename, std::ios::app);
    file << dtb << std::endl;
}

bool dtbcheck = true;
void Memory::open_proc(const char *name)
{
    // Ensure the DTB file exists
    ensure_file_exists(dtb_filename);

    if (!conn)
    {
        conn = std::make_unique<ConnectorInstance<>>();
        Inventory *inv = inventory_scan();

        printf("Init with qemu connector...\n");
        if (!kernel_init(inv, "qemu"))
        {
            printf("Init with kvm connector...\n");
            if (!kernel_init(inv, "kvm"))
            {
                printf("Quitting\n");
                inventory_free(inv);
                exit(1);
            }
        }

        printf("Kernel initialized: %p\n", kernel.get()->container.instance.instance);
    }

    ProcessInfo info;
    info.dtb2 = Address_INVALID;

    if (kernel.get()->process_info_by_name(name, &info))
    {
        status = process_status::NOT_FOUND;
        return;
    }

    ProcessInstance<> tmp_proc;

    if (kernel.get()->process_by_info(info, &tmp_proc))
    {
        status = process_status::NOT_FOUND;
        return;
    }

    ModuleInfo module_info;
    std::set<size_t> valid_dtbs = load_valid_dtbs(dtb_filename);

    if (tmp_proc.module_by_name(name, &module_info))
    {
        printf("\nSearching for a valid DTB in valid_dtbs.txt...\n");
        
        bool found = false;

        // First check existing valid DTBs
        for (size_t dtb : valid_dtbs)
        {
            info.dtb1 = dtb;
            kernel.get()->process_by_info(info, &tmp_proc);

            if (!tmp_proc.module_by_name(name, &module_info))
            {
                printf("\nUsing existing dtb: %zu\n", dtb);
                found = true;
                break;
            }
        }

        // If not found, search for a new DTB
        if (!found)
        {
			printf("\nNo valid DTB in valid_dtbs.txt, Searching for a new DTB...\n");
            for (size_t dtb = 0; dtb <= SIZE_MAX; dtb += 0x1000)
            {
                info.dtb1 = dtb;
                kernel.get()->process_by_info(info, &tmp_proc);

                if (!tmp_proc.module_by_name(name, &module_info))
                {
                    printf("\nFound new dtb: %zu\n", dtb);
                    append_valid_dtb(dtb_filename, dtb);
                    found = true;
                    break;
                }

                if (dtb == SIZE_MAX)
                {
                    printf("Access error for process %s\n", name);
                    status = process_status::FOUND_NO_ACCESS;
                    return;
                }
            }
        }
    }

    kernel.get()->clone().into_process_by_info(info, &proc.hProcess);

    proc.baseaddr = module_info.base;
    status = process_status::FOUND_READY;
}

void Memory::close_proc()
{
	proc.baseaddr = 0;
}

/* uint64_t Memory::ScanPointer(uint64_t ptr_address, const uint32_t offsets[], int level)
{
	if (!ptr_address)
		return 0;

	uint64_t lvl = ptr_address;

	for (int i = 0; i < level; i++)
	{
		if (!Read<uint64_t>(lvl, lvl) || !lvl)
			return 0;
		lvl += offsets[i];
	}

	return lvl;
} */