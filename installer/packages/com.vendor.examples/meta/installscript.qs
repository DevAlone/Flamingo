function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows") {
        component.addOperation("Extract", "example.zip", "@HomeDir@/flamingo_courses/");
    }
}
