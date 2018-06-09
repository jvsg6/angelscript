class Inherit
{
	Inherit(){print("Constructor\n");}
	// A class method
    
	void PreDrawPhase()
	{
		print("PreDrawPhase()\n");
	}

	void PostDrawPhase()
	{
		print("void PostDrawPhase()\n");
	}
	int CheckInt()
	{
		return 123456.7;
	}
	void IfInt(int a)
	{
		
		if (a == 1)
		{
			print("Yess, im work!!!");
		}
		else
		{
			print("Nonononon");
		}
	}
	void DoSomething()
	{
		// The class properties can be accessed directly
		a *= 2;
		// The declaration of a local variable may hide class properties
		int b = 42;
		// In this case the class property have to be accessed explicitly
		this.b = b;
		print ("Im Do something");
	}
		// Class properties
		int a;
		int b;
}
