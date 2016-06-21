#include <inc/mmu.h>
#include <inc/memlayout.h>


// The entry.S page directory maps the first 4MB of physical memory
// starting at virtual address KERNBASE (that is, it maps virtual
// addresses [KERNBASE, KERNBASE+4MB) to physical addresses [0, 4MB)).
// We choose 4MB because that's how much we can map with one page
// table and it's enough to get us through early boot.  We also map
// virtual addresses [0, 4MB) to physical addresses [0, 4MB); this
// region is critical for a few instructions in entry.S and then we
// never use it again.
//
// Page directories (and page tables), must start on a page boundary,
// hence the "__aligned__" attribute.  Also, because of restrictions
// related to linking and static initializers, we use "x + PTE_P"
// here, rather than the more standard "x | PTE_P".  Everywhere else
// you should use "|" to combine flags.
__attribute__((__aligned__(NPTENTRIES << 2)))
pde_t entry_pgdir[NPTENTRIES] = {
	// Map VA's [0, 4MB) to PA's [0, 4MB)
	[0] = (unsigned)PGADDR(0, 0, 0) | PTE_P | PTE_SWO,
	[1] = (unsigned)PGADDR(0, 1, 0) | PTE_P | PTE_SWO,
	[2] = (unsigned)PGADDR(0, 2, 0) | PTE_P | PTE_SWO,
	[3] = (unsigned)PGADDR(0, 3, 0) | PTE_P | PTE_SWO,
	// Map VA's [KERNBASE, KERNBASE+4MB) to PA's [0, 4MB)
	[(KERNBASE>>PTXSHIFT) + 0] = (unsigned)PGADDR(0, 0, 0) | PTE_P | PTE_SWO,
	[(KERNBASE>>PTXSHIFT) + 1] = (unsigned)PGADDR(0, 1, 0) | PTE_P | PTE_SWO,
	[(KERNBASE>>PTXSHIFT) + 2] = (unsigned)PGADDR(0, 2, 0) | PTE_P | PTE_SWO,
	[(KERNBASE>>PTXSHIFT) + 3] = (unsigned)PGADDR(0, 3, 0) | PTE_P | PTE_SWO
};
