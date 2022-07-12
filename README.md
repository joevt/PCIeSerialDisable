# PCIeSerialDisable

OpenCore added a quirk to enable the macOS xnu kernel to use a serial port other than the default COM1 port.

- https://github.com/acidanthera/bugtracker/issues/1954
- https://github.com/acidanthera/OpenCorePkg/pull/330
- https://github.com/acidanthera/OpenCorePkg/pull/331
- https://github.com/acidanthera/bugtracker/issues/2003
- https://github.com/acidanthera/OpenCorePkg/commit/59fd52487970a66def8b7fac71b10859902f3f55

The purpose of the original version of PCIeSerialDisable.kext (created in one of the above links) is to block the serial port from being used by macOS user apps so that the kernel could continue to use it for logging. It was a codeless kext containing an Info.plist file with one IOKit personality that matches the single PCIe serial port that was reserved for xnu by OpenCore. It blocks Apple's serial port driver from matching the same serial port which would have stopped the serial port from working until it was opened by an app. This worked on my iMac14,2.

On my Macmini8,1, the original version of PCIeSerialDisable.kext is not sufficient in keeping the serial port enabled for xnu.

- https://github.com/acidanthera/bugtracker/issues/2075

I have not tracked down the process that disables the serial port (probably PCIe/Thunderbolt enumeration?). This new version contains code to reenable the serial port just in case it was disabled.

Since the kext now includes code, The OpenCore config.plist needs to include the new binary information:
```
			<dict>
				<key>Arch</key> <string>Any</string>
				<key>BundlePath</key> <string>PCIeSerialDisable.kext</string>
				<key>Comment</key> <string>PCIeSerialDisable</string>
				<key>Enabled</key> <true/>
				<key>ExecutablePath</key> <string>Contents/MacOS/PCIeSerialDisable</string>
				<key>MaxKernel</key> <string></string>
				<key>MinKernel</key> <string></string>
				<key>PlistPath</key> <string>Contents/Info.plist</string>
			</dict>
```

Another issue for my Macmini8,1 is that `serial_init` does not get called or it doesn't enable xnu serial port output. For this, I made Lilu.kext call `serial_init` itself.
- https://q.gudangbibitku.com/host-https-github.com/joevt/Lilu/commit/c5d0525571e1f1860f5740a2d6289cf156ce19a9
