function Component()
{
    // default constructor
}

Component.prototype.create.OperationsForArchive = function(archive)
{
	component.addOperation("Extract", archive, "@TargetDir@/subdir/");
}
