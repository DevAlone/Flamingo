function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut", "@TargetDir@/flamingo.exe", "@StartMenuDir@/flamingo.lnk",
            "workingDirectory=@TargetDir@", "iconPath=@TargetDir@/icon.ico",
            "iconId=2");
	
	if(systemInfo.currentCpuArchitecture.search("64") < 0) {
		// x86 
		component.addOperation("Execute", "@TargetDir@/vcredist_x86.exe", "/quiet", "/norestart");
		
	} else {
		// x64
		component.addOperation("Execute", "@TargetDir@/vcredist_x64.exe", "/quiet", "/norestart");
	}
    }
}
