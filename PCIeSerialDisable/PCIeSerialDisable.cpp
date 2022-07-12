#include "PCIeSerialDisable.hpp"

#define super IOService

OSDefineMetaClassAndStructors(PCIeSerialDisable, IOService)

IOService *PCIeSerialDisable::
probe(IOService *provider, SInt32 *score)
{
	Provider = OSDynamicCast(IOPCIDevice, provider);
	if (!Provider) {
		IOLog ("PCIeSerialDisable: Attached to non-IOPCIDevice provider! Failing probe()\n");
		return NULL;
	}

	if (!super::probe(provider, score)) return NULL;

	Provider->setIOEnable(true);
	return this;
}

bool PCIeSerialDisable::
start(IOService *provider)
{
	IOLog("PCIeSerialDisable::start ID=%04x:%04x SID=%04x:%04x Class=%02x:%02x:%02x Int=%d\n",
		(int)(Provider->configRead16(kIOPCIConfigVendorID)),
		(int)(Provider->configRead16(kIOPCIConfigDeviceID)),
		(int)(Provider->configRead16(kIOPCIConfigSubSystemVendorID)),
		(int)(Provider->configRead16(kIOPCIConfigSubSystemID)),
		(int)(Provider->configRead8(kIOPCIConfigClassCode+2)),
		(int)(Provider->configRead8(kIOPCIConfigClassCode+1)),
		(int)(Provider->configRead8(kIOPCIConfigClassCode+0)),
		(int)(Provider->configRead8(kIOPCIConfigInterruptPin))
	);
	
	if (!super::start(provider)) return false;
	
	Provider->setIOEnable(true);
	return true;
}

void PCIeSerialDisable::
stop(IOService *provider)
{
	IOLog("PCIeSerialDisable::stop(%p)\n", provider);
	super::stop(provider);
}

void PCIeSerialDisable::
free()
{
	IOLog("PCIeSerialDisable::free()\n");
	super::free();
}
