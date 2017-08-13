function Component()
{
    // default constructor
}

Component.prototype.createOperationsForArchive = function(archive)
{
	component.addElevatedOperation("Extract", archive, "@TargetDir@/subdir/");
}
