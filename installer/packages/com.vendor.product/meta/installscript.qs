Component.prototype.createOperations = function()
{
	component.createOperations();
	if(systemInfo.productType == "windows") {
		component.addOperation("CreateShortcut", "@TargetDir@/flamingo.exe", "@StartMenuDir@/flamingo/flamingo.lnk", "workingDirectory=@TargetDir@", "iconPath=icon.ico", "iconId=2");
	}
}
