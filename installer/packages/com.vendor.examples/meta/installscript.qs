function Component()
{
    // default constructor
}

Component.prototype.createOperationsForArchive = function(archive)
{
	component.addOperation("Extract", archive, "@HomeDir@/");
}
