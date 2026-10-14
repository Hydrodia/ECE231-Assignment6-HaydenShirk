#include <iostream>
#include <cmath>
#include "coordinate.h"

using namespace std;

int main(int argc, char *argv[]){

    //chacks to see if there is a command line argument and is vaild
    if(argc != 2){
	cout << "Usage: " << argv[0] << "number of corrdinates" << endl;
	return 1;
    }

    char *endptr;
    long count = strtol(argv[1], &endptr, 10);

    if(*argv[1] == '\0' || *endptr != '\0' || count < 0 || count > 1000000){
	cout << "Please enter a vaild non-negative integer." << endl;
	return 1;
    }
    
    //initalize the random number generator for the coordinates
    srand(static_cast<unsigned int>(time(nullptr)));

    //create beginning and end nodes
    Coordinate *list_beginning = new Coordinate;
    Coordinate *list_end = new Coordinate;

    list_beginning->coord_id = -1;
    list_end->coord_id = -1;

    list_beginning->previous = nullptr;
    list_beginning->next = list_end;

    list_end->previous = list_beginning;
    list_end->next = nullptr;

    //generate the random coorinates
    for(int i = 0; i < count; i++){
	float x = static_cast<float>(rand() % 1000) / 10.0f;
	float y = static_cast<float>(rand() % 1000) / 10.0f;

	add_coordinate(list_end, x, y);
    }

    //Display list in both directions
    forward_display(list_beginning);
    backward_display(list_end);

    //Display the length of the list
    cout << "\nList Length: " << list_length(list_beginning) << endl;
    
    //Find closet coordinate to 50, 50
    closest_to(list_beginning, 50.0f, 50.0f);

    //Deletes a coordinate
    if(count > 0){
	int idToDelete = (count >= 2) ? 2 : 1;
	delete_coordinate(list_beginning, idToDelete);
    }

    //Display list after deletion
    forward_display(list_beginning);

    cout << "\nList length after deletion: " << list_length(list_beginning) << endl;

   //free remaining memory
   Coordinate *current = list_beginning->next;

   while(current != list_end){
	Coordinate *nextNode = current->next;
	delete current;
	current = nextNode;
   }

   delete list_beginning;
   delete list_end;

   return 0;
}

//function that gets the length of the list
int list_length(Coordinate *list_beginning){
    int length = 0;
    Coordinate *current = list_beginning->next;

    while(current->coord_id != -1){
	length++;
	current = current->next;
    }
    
    return length;
}

//function that adds a coordinate to the list
void add_coordinate(Coordinate *list_end, float x, float y){
    Coordinate *newNode = new Coordinate;

    newNode->x = x;
    newNode->y = y;

    //assign id basde on current length list
    int length = 0;
    Coordinate *current = list_end->previous;

    while(current->coord_id != -1){
	length++;
	current = current->previous;
    }
    newNode->coord_id = length + 1;

    newNode->next = list_end;
    newNode->previous = list_end->previous;

    list_end->previous->next = newNode;
    list_end->previous = newNode;
}

//function to display list from beginning to end
void forward_display(Coordinate *list_beginning){
    Coordinate *current = list_beginning->next;

    cout << "\nForward List:\n";

    while(current->coord_id != -1){
	cout << "ID " << current->coord_id << ": (" << current->x << "," << current->y << ")" << endl;

	current = current->next;
    }
}

//function to display list from the end to the beginning
void backward_display(Coordinate *list_end){
    Coordinate *current = list_end->previous;

    cout << "\nBackward List:\n";

    while(current->coord_id != -1){
	cout << "ID " << current->coord_id << ": (" << current->x << "," << current->y << ")" << endl;

	current = current->previous;
    }
}

//function to delete a coordinate
void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete){
    Coordinate *current = list_beginning->next;

    while(current->coord_id != -1){
	if(current->coord_id == coord_id_to_delete){
	    current->previous->next = current->next;
	    current->next->previous = current->previous;

	    cout << "Deleted Coordinate ID: " << current->coord_id << endl;

	    delete current;
	    return;
	}
	current = current->next;
    }
    cout << "Coordinate ID " << coord_id_to_delete << "was not found!" << endl;
}

//function to find the closet coordinate point to the provided values
void closest_to(Coordinate *list_beginning, float x, float y){
    Coordinate *current = list_beginning->next;
    Coordinate *closest = nullptr;
    float shortestDistance = 0.0f;

    while(current->coord_id != -1){
	float dx = current->x - x;
	float dy = current->y - y;

	float distance = sqrt(dx * dx + dy * dy);

	if(closest == nullptr || distance < shortestDistance){
	    shortestDistance = distance;
	    closest = current;
	}
	current = current->next;
    }

    cout << "\nFinding the point closest to (" << x << "," << y << ")" << endl;

    if(closest != nullptr){
	cout << "Closest coordinate ID " << closest->coord_id << ": (" << closest->x << "," << closest->y << ")" << endl;

	cout << "Distance: " << shortestDistance << endl;
    }
    else{
	cout << "The list is empty!" << endl;
    }
}
