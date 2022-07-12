#ifndef _PCIESERIALDISABLE_H
#define _PCIESERIALDISABLE_H

#include <IOKit/pci/IOPCIDevice.h>

class PCIeSerialDisable : public IOService
{
	OSDeclareDefaultStructors(PCIeSerialDisable);

public:
	virtual IOService *probe(IOService *provider, SInt32 *score) override;
	virtual bool start(IOService *provider) override;
	virtual void stop(IOService *provider) override;
	virtual void free() override;

protected:
	IOPCIDevice *Provider;
};

#endif /* !_PCIESERIALDISABLE_H */
