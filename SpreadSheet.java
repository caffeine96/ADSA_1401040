
class Node
{
	int value;
	public string index;
	
	public Node next,prev;
	public Node in1,in2;
	public Node out1,out2;
	
	Node(int val,String ind)
	{
		value=val;
		index=new String(ind);
		
		next=prev=null;
		in1=in2=null;
		out1=out2=null;
	}
	
	Node(string val,String ind)
	{
		equation(val);
		value=calculate();
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
		
	}
	
	
	public void changeval(int val, int ind) 
	{
		Node temp=start;
		
		for(;temp==rear;temp=temp.next)
		{
			if(temp.index==ind)
			{
				temp.val=val;
				temp.out1.val=temp.out1.calculate();
				temp.out2.val=temp.out2.calculate();
				break;
			}	
		}	
		
	}
}


class SpreadSheet
{

	public static void main()
	{
		
		
	}
}