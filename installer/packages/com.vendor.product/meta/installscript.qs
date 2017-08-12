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
    }
}
