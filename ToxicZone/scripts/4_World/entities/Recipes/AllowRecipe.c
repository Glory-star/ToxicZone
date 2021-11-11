#ifndef GASMASKADDON
modded class PluginRecipesManager
{
	override void RegisterRecipies()
	{
		super.RegisterRecipies();
		RegisterRecipe(new FillFilter);
		RegisterRecipe(new FillFilterfive);
		RegisterRecipe(new FillFilterten);
	}
}
#endif
