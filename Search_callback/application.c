#include "dll.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*Application specific data structures*/
typedef struct student_{

    char name[32];
    int age;
    int weight;
    unsigned int rollno;
} student_t;

static void
print_student_details(student_t *student){

    printf("Name = %s\n",   student->name);
    printf("Age = %d\n",    student->age);
    printf("weight = %d\n", student->weight);
    printf("rollno = %u\n", student->rollno);
    printf("\n");
}

static void
print_student_db(dll_t *student_db) {

    if(!student_db || !student_db->head) return;

#if 0
    struct Node *head = student_db->head;
    student_t *data = NULL;

    while(head){
        data = head->data;
        print_student_details(data);
        head = head->next;    
    }
#endif
    struct Node *head = NULL;
    student_t *data = NULL;

    ITERATE_LIST_BEGIN(student_db,head){

        data = head->data;
        print_student_details(data);
    } ITERATE_LIST_END;
}

/*Application specific data structures*/
typedef struct employee_{

    char name[32];
    char designation[32];
    unsigned int salary;
    unsigned int emp_id;
} employee_t;

static void print_employee_details(employee_t *employee)
{

    printf("Name = %s\n",   employee->name);
    printf("Designation = %s\n",    employee->designation);
    printf("salary = %u\n", employee->salary);
    printf("emp_id = %u\n", employee->emp_id);
    printf("\n");
}

static void print_employee_db(dll_t *employee_db) 
{
    if(!employee_db || !employee_db->head) return;

    struct Node *head = employee_db->head;
    employee_t *data = NULL;

    while(head){
        data = head->data;
        print_employee_details(data);
        head = head->next;    
    }
}

/* Traditional search function implemented by application itself for finding student by roll no*/
student_t *search_student_by_rollno(dll_t *student_db, unsigned int rollno/*search key*/)
{
   if(!student_db || !student_db->head) return NULL;

    struct Node *head = student_db->head;
    student_t *data = NULL;

    while(head){
        data = head->data;
        if(data->rollno == rollno)
            return data;
        head = head->next;    
    }
}


/* Traditioanl search function implemented by application itself for finding particualr employee using employee id*/
employee_t * search_employee_by_emp_id(dll_t *employee_db, unsigned int emp_id/*search key*/)
{
   if(!employee_db || !employee_db->head) return NULL;

    struct Node *head = employee_db->head;
    employee_t *data = NULL;

    while(head){
        data = head->data;
        if(data->emp_id == emp_id)
            return data;
        head = head->next;    
    }
}


/*Search callbacks*/
static int /*return 0 if matches, return -1 if do not match*/
search_student_db_by_key(void *data, void *key)
{
    student_t *student = (student_t *)data;
    char* name = (char*)key;
    if(!strcmp(student->name, name))
       return 0;
    return -1;
}

/*Search callbacks*/
static int /*return 0 if matches, return -1 if do not match*/
search_employee_db_by_key(void *data, void *key)
{
    employee_t *emp = (employee_t *)data;
    unsigned int emp_id = (unsigned int)key;
    if(emp->emp_id == emp_id)
        return 0;
    return -1;
}



int main(int argc, char **argv)
{
    /*Student database*/
    student_t *student1 = calloc(1, sizeof(student_t));
    strncpy(student1->name, "Abhishek", strlen("Abhishek"));
    student1->age = 31;
    student1->weight = 75;
    student1->rollno = 800000;

    student_t *student2 = calloc(1, sizeof(student_t));
    strncpy(student2->name, "Joseph", strlen("Joseph"));
    student2->age = 41;
    student2->weight = 70;
    student2->rollno = 800400;

    student_t *student3 = calloc(1, sizeof(student_t));
    strncpy(student3->name, "Jack", strlen("Jack"));
    student3->age = 29;
    student3->weight = 55;
    student3->rollno = 800400;

    /*Create a new Linked List*/

    dll_t *student_db = get_new_dll();
    register_key_match_callback(student_db, search_student_db_by_key);

    Add_front(student_db, student1);
    Add_front(student_db, student2);
    Add_front(student_db, student3);
 
    printf("Data before we search and delete\n");
    print_student_db(student_db); 

    /*student_t *student = search_student_by_rollno(student_db, 800400); */
   /*student_t *student = dll_search_by_key(student_db, (void *)800400);  */
   /* struct Node *student = dll_search_by_key(student_db, (void *)800400); */
    //struct Node *student = dll_search_by_key(student_db, (void *)"Abhishek");
    student_t* student = dll_search_by_key(student_db, (void *)"Abhishek");
    if(!student){
        printf("Student record not found\n");
    }
    else{
        printf("The founded record is this which will get deleted.\n");
        print_student_details(student);
        delete_node_by_value(student_db, student);
        //struct Node* node = student_db->head;
        //deleteNode(student_db, student_db->head);
        //removeNode(student_db, student_db->head); 
        //Add_Node_front(student_db, node); 
        //print_student_details(node->data);
        //deleteNode(student_db, node);
        printf("The new data record will be as follows.\n");
        print_student_db(student_db);
        printf("\n******************\n");
        reverse(student_db);
        print_student_db(student_db);
        Detect_remov_loop(student_db);
    }

 #if 0
    struct Node* node1 = (struct Node*)calloc(1,sizeof(struct Node)); 
    struct Node* node2 = (struct Node*)calloc(1,sizeof(struct Node));
    struct Node* node3 = (struct Node*)calloc(1,sizeof(struct Node));

    node1->data = student1; 
    node1->prev = NULL; 
    node1->next = node2; 

    node2->data = student2; 
    node2->prev = node1; 
    node2->next = node3; 

    node3->data = student3; 
    node3->prev = node2; 
    node3->next = node1; 

    dll_t *nodes = get_new_dll();
    nodes->head =  node1;
    printf("\nFor new database\n");
    //print_student_db(nodes);
    Detect_remov_loop(nodes);
    printf("\nAfter loop Removal\n");
    Detect_remov_loop(nodes);
    print_student_db(nodes);
#endif

    
/*
    //Employee database
    employee_t *employee1 = calloc(1, sizeof(employee_t));
    strncpy(employee1->name, "Harsh", strlen("Harsh"));
    strncpy(employee1->designation, "Vice President", strlen("Vice President"));
    employee1->salary = 11131;
    employee1->emp_id = 10000;

    employee_t *employee2 = calloc(1, sizeof(employee_t));
    strncpy(employee2->name, "Huma", strlen("Huma"));
    strncpy(employee2->designation, "CEO", strlen("CEO"));
    employee1->salary = 127000;
    employee1->emp_id = 10001;

    employee_t *employee3 = calloc(1, sizeof(employee_t));
    strncpy(employee3->name, "Neena", strlen("Neena"));
    strncpy(employee2->designation, "Manager", strlen("Manager"));
    employee1->salary = 139000;
    employee1->emp_id = 10002;

    /*Create a new Linked List

    dll_t *employee_db = get_new_dll();
    register_key_match_callback(employee_db, search_employee_db_by_key);
    add_data_to_dll(employee_db, employee1);
    add_data_to_dll(employee_db, employee2);
    add_data_to_dll(employee_db, employee3);

    //employee_t *employee = search_employee_by_emp_id(employee_db, 10002);
    employee_t *employee = dll_search_by_key(employee_db, (void *)10002);
    if(!employee){
        printf("Student record not found\n");
    }
    else{
        print_employee_details(employee);    
    }
   */
    return 0;
}
