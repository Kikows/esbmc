#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cxlmem.h"
#include "linux/pci.h"
#include "cxl.h"

// Macro definitions
#define CXL_REGLOC_RBI_COMPONENT 1
#define CXL_REGLOC_RBI_MEMDEV 2

int cxl_map_component_regs(struct pci_dev *pdev,
			   struct cxl_component_regs *regs,
			   struct cxl_register_map *map){
    (void) pdev;
    (void) regs;
    (void) map;
    
    // Check pre-conditions
    assert(regs != NULL);
    assert(map != NULL);
    
    return 0;		   
};
int cxl_map_device_regs(struct pci_dev *pdev,
			struct cxl_device_regs *regs,
			struct cxl_register_map *map){	
    (void) pdev;
    (void) regs;
    (void) map;
    
    // Check pre-conditions
    assert(regs != NULL);
    assert(map != NULL);
    
    return 0;						
};

// Abstract function
int cxl_map_regs(struct cxl_dev_state *cxlds, struct cxl_register_map *map) {
    
    // Check pre-conditions
    assert(cxlds != NULL);
    assert(map != NULL);

   struct device *dev = cxlds->dev;
   struct pci_dev *pdev = to_pci_dev(dev);
   
    switch (map->reg_type) {
        case CXL_REGLOC_RBI_COMPONENT:
            cxl_map_component_regs(pdev, &cxlds->regs.component, map);
            printf("Mapping component registers...\n");
            break;
        case CXL_REGLOC_RBI_MEMDEV:
            cxl_map_device_regs(pdev, &cxlds->regs.device_regs, map);
            printf("Probing device registers...\n");
            break;
        default:
            printf("Unknown register type.\n");
            break;
    }
    return 0;
}

// Main test function
int main() {
    struct cxl_dev_state *dev_state = (void *) 0x11111;
    struct cxl_register_map *register_map_component = (void *) 0x22222;
    struct cxl_register_map *register_map_memdev = (void *) 0x33333;
    struct cxl_register_map *register_map_unknown = (void *) 0x44444;

    int result = cxl_map_regs(dev_state, register_map_component);
    // Check post-conditions
    assert(result == 0);
    
    result = cxl_map_regs(dev_state, register_map_memdev);
    // Check post-conditions
    assert(result == 0);
    
    result = cxl_map_regs(dev_state, register_map_unknown);
    // Check post-conditions
    assert(result == 0);
    
    return 0;
}

