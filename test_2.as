class Inherit_2
{
	Inherit_2()
	{
	print("Constructor_2\n");
	}
	// A class method
    
	void PreDrawPhase()
	{
		print("PreDrawPhase_2()\n");
	}

	void PostDrawPhase()
	{
		print("Call function PostDrawPhase_2\n");
	}
	int CheckInt()
	{
		return 2222.7;
	}
	void IfInt(int a)
	{
		
		if (a == 1)
		{
			print("Take a_2\n");
		}
		else
		{
			print("Can't take a_2\n");
		}
	}
}
