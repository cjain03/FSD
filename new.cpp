#include<iostream>
#include<cstring>
using namespace std ;
class gnode
{
    int id;
    string username;
    gnode * next;
    public:
        gnode()
        {
            id=-1;
            username='\0';
            next=NULL;
        }
    friend class graph;
};
class graph
{
    int n;
    gnode *head[10];
    public:
        graph()
        {
            n=0;
            cout<<"accept no of friends: ";
            cin>>n;
            for (int i=0;i<n;i++)
            {
                head[i]=new gnode;
                head[i]->id=i;
                cout<<"accept name of friend: ";
                cin>>head[i]->username;
            }
        }
    void create();
    void display();
    void dfs_r();
        void dfs_r(int, int*);
    void dfs_nr(int);
    void bfs_nr(int);
    friend class stack;
};
class stack
{
    int top;
    int s[10];
    public:
        stack()
        {
            top=-1;
        }
    void push(int temp);
    int pop();
    int isempty();
    int isfull();
};

class queue
{
    int front,rear;
    int q[20];
    public:
        queue()
        {
            front=rear=-1;
        }
    void enqueue(int temp);
    int dequeue();
    int isempty();
    int isfull();
};
void stack::push(int temp)
{
    if(!isfull())
    {
        top++;
        s[top]=temp;;
    }
}

int stack::pop()
{
    int temp;
    if(!isempty())
    {
        temp=s[top];
        top--;
        return temp;
    }
    else
        return -1;
    
}

int stack:: isempty()
{
    if(top==-1)
        return 1;
    else
        return 0;
}

int stack :: isfull()
{
    if(top==9)
        return 1;
    else
        return 0;
}

void queue::enqueue(int temp)
{
    if(!isfull())
    {
        rear++;
        q[rear]=temp;;
    }
}

int queue:: dequeue()
{
    int temp;
    if(isempty()!=1)
    {
        front++;
        temp=q[front];
        return temp;
    }
    else
        return -1;
    
}

int queue:: isempty()
{
    if(rear==front)
        return 1;
    else
        return 0;
}

int queue :: isfull()
{
    if(rear==19)
        return 1;
    else
        return 0;
}

void graph ::create()
{
    char d;
    int id;
    gnode *temp,*current;

    for(int i=0;i<n;i++)
    {
        temp=head[i];
        cout<<"--------------"<<endl;
        cout<<"enter the friends of "<<head[i]->username<<":"<<endl;
        do
        {
            cout<<"enter id: "<<endl;
            cin>>id;
            if(id==head[i]->id)
            {
                cout<<"you cannot be your own friend";
            }
            else
            {
                current=new gnode;
                current->id=id;
                current->username=head[id]->username;
                temp->next=current;
                temp=temp->next;
            }
            cout<<"do you want to add more friends: ? (Y/n)"<<endl;
            cin>>d;
        }
        while(d=='y' || d=='Y');
    }
}
void graph:: display()
{
    
    for(int i=0;i<n;i++)
    {
        gnode *temp=head[i]->next;
        cout<<"\n Friends of "<<head[i]->username;
        while(temp!=NULL)
        {
            cout<<"-"<<temp->username;
            temp=temp->next;
        }
        cout<<endl;
    }
}

void graph :: dfs_r()
{
    int user[10];
    for (int i=0;i<n;i++)
        user[i]=0;
    int uid;
    cout<<"enter the starting id of user: "<<endl;
    cin>>uid;
    dfs_r(uid,user);
    cout<<endl;
}

void graph :: dfs_r(int v,int user[10])
{
    cout<<head[v]->username<<'\t';
    user[v]=1;
    gnode *temp=head[v]->next;
    while(temp!=NULL)
    {
        if(!user[temp->id])
        {
            dfs_r(temp->id,user);
        }
        temp=temp->next;
    }
}

void graph:: dfs_nr(int v)
{
    int user[10];
    for(int i=0;i<n;i++)
        user[i]=0;
    stack s;
    s.push(v);
    user[v]=1;
    do
    {
        v=s.pop();
        cout<<head[v]->username<<'\t';
        gnode *temp=head[v]->next;
        while(temp!=NULL)
        {
            if(!user[temp->id])
            {
                s.push(temp->id);
                user[temp->id]=1;
            }
            temp=temp->next;
        }
    }while(!s.isempty());
}

void graph :: bfs_nr(int v)
{
    int user[10];
    for(int i=0;i<n;i++)
        user[i]=0;
    queue q;
    q.enqueue(v);
    user[v]=1;
    while(!q.isempty())
    {
        v=q.dequeue();
        cout<<head[v]->username<<'\t';
        gnode * temp=head[v]->next;
        while(temp!=NULL)
        {
            if(!user[temp->id])
            {
                q.enqueue(temp->id);
                user[temp->id]=1;
            }
            temp=temp->next;
        }
    }
    cout<<endl;
}
int main()
{
    graph g;
    g.create();
    g.display();
    cout<<"dfs recursive"<<endl;
    g.dfs_r();
    cout<<"dfs non recursive"<<endl;
    g.dfs_nr(0);    
    cout<<endl;
    cout<<"bfs"<<endl;
    g.bfs_nr(0);
}
