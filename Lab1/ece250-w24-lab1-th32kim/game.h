// define your classes here...
class LinkedList{
    class Node{
        public:
            double x;
            double y;
            double distance;
            Node *next;
            //Node Constructor
            Node(double input_x, double input_y);
    };
    //Linked List private variable
    private:
        int numPlayer;
        Node *head;
        Node *tail;

    public:
        LinkedList();
        void Spawn(double spawn_x, double spawn_y);
        void Time(double t);
        void Lunch();
        void Num();
        void PRT(double d);
        void OVER();
        ~LinkedList();
        //Print Test!!!! Delete afterrrr
        void display();
        //////////////////////////////

};