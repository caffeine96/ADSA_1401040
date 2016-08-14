
class Node
{
	int value;
	public String index;
	
	public Node next,prev;
	public int coeff1,coeff2;
	public char op;
 	public Node in1,in2;
	public Node out1,out2;
	
	public int calculate()
	{
		int temp_val=0;
		
		if(in2!=null)
		{	
			switch(op)
			{
				case '+':
							temp_val=coeff1*in1.value+coeff2*in2.value;
							break;
							
				case '-':
							temp_val=coeff1*in1.value-coeff2*in2.value;
							break;			
							
				case '/':
							temp_val=(coeff1*in1.value)/(coeff2*in2.value);
							break;			
				
				case '*':
							temp_val=coeff1*in1.value*coeff2*in2.value;
							break;	
			}
		}	
		else
			temp_val=coeff1*in1.value;
		
		if(out1!=null)
		{	
			out1.calculate();
		
			if(out2!=null)
				out2.calculate();
		}	
		
		return temp_val;
	}
	
	
	Node(int val,String ind)
	{
		value=val;
		index=new String(ind);
		coeff1=coeff2=0;
		op='+';
		next=prev=null;
		in1=in2=null;
		out1=out2=null;
	}
	
	Node(String val,String ind)
	{
		index=new String(ind);
		
		next=prev=null;
		in1=in2=null;
		out1=out2=null;
	}
	
}

class List
{
	public Node start,rear;
	
	List()
	{
		start=rear=null;
	}
	
	public void add(int x,String y)
	{
		Node newnode= new Node(x,y);
		
		if(start==null)
			start=rear=newnode;
		else
		{
			rear.next=newnode;
			newnode.prev=rear;
			rear=newnode;
		}	
		
	}
	
	public void add(String x,String y)
	{
		Node newnode= new Node(x,y);
		
		if(start==null)
			start=rear=newnode;
		else
		{
			rear.next=newnode;
			newnode.prev=rear;
			rear=newnode;
		}

		newnode.coeff1=(x.charAt(0)+2)%10;
		newnode.in1=searchin(x.charAt(1),x.charAt(2));

		
		if(x.length()>3)
		{
			newnode.in2=searchin(x.charAt(5),x.charAt(6));
			newnode.op=x.charAt(3);
			newnode.coeff2=(x.charAt(4)+2)%10;
		}
		
		newnode.value=newnode.calculate();
	}
	
	public Node searchin(char a1,char a2)
	{
		for(Node temp=start;temp!=null;temp=temp.next)
		{
			if((temp.index.charAt(0)==a1)&&(temp.index.charAt(1)==a2))
				return temp;
		}
		
		return null;
	}
	
	public void display(String x)
	{
		for(Node temp=start;temp!=null;temp=temp.next)
		{
			if((temp.index.charAt(0)==x.charAt(0))&&(temp.index.charAt(1)==x.charAt(1)))
				System.out.println(temp.value);
		}
		
	}
	
	
	public void changeval(int val, String ind) 
	{
		for(Node temp=start;temp!=null;temp=temp.next)
		{
			if(temp.index==ind)
			{
				temp.value=val;
				
				if(temp.out1!=null)
					temp.out1.value=temp.out1.calculate();
				
				if(temp.out2!=null)
					temp.out2.value=temp.out2.calculate();
				
				break;
			}	
		}	
		
	}
}


class SpreadSheet
{

	public static void main(String args[])
	{
		List l=new List();
		
		try
		{
			l.add(3,"a1");
			l.add(4,"a2");
			l.add("3a1+2a2","a3");
			l.add("2a3+3a1","a4");
			l.display("a1");
			l.display("a2");
			l.display("a3");
			l.display("a4");
		}
		catch(Exception e)
		{
			System.out.println("Illegal Formula");
		}
	}
}