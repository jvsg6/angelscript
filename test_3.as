class Inherit
{
	Inherit()
	{
	print("Constructor\n");
	}
	// A class method
    
	void PreDrawPhase()
	{
		print("PreDrawPhase()\n");
	}

	void PostDrawPhase()
	{
		print("Call function PostDrawPhase\n");
	}
	int CheckInt()
	{
		return 123456.7;
	}
	void IfInt(int a)
	{
		
		if (a == 1)
		{
			print("Take a\n");
		}
		else
		{
			print("Can't take a\n");
		}
	}
}
