/*
 * IsisCourse.cpp
 *
 */

#include <iostream>
#include "IsisCourse.h"

IsisCourse::IsisCourse() {
	class_capacity = 0; // no students allowed in yet
}

IsisCourse::IsisCourse(int init_capacity) {
	// TODO: Student writes code here

	class_capacity = init_capacity;
}

IsisCourse::~IsisCourse() {
	// nothing to do
}

void IsisCourse::set_class_cap(int cap) {
	class_capacity = cap;
	if (roster.size() < class_capacity) {
		update_enrollments();
	}
}

IsisCourse::ENROLLMENT_STATUS IsisCourse::enroll_student(Student s) {
	// See the enrollment logic from the assignment handout or
	// the IsisCourse.h file!
	// TODO: Student writes code here

	//check if the student is major or non-major
	if (s.major) {
		//major students

		//if the class is not full, add to the roster
		if (roster.size() < class_capacity) {
			//if add the student successfully, return ENROLLED
			//otherwise return NONE
			if (roster.add(s))
				return ENROLLED;
			else
				return NONE;
		}
		else {
			//the roster is full
			//add the student to the major waitlist
			major_waitlist.enqueue(s);

			//return status MAJOR_WAITLIST
			return MAJOR_WAITLIST;
		}
	}
	else {
		//non-major students
		//add them to the other waitlist
		other_waitlist.enqueue(s);

		//return status OTHER_WAITLIST
		return OTHER_WAITLIST;
	}

}

bool IsisCourse::drop_student(Student s) {
	bool found_student = false; // if we find the student to drop
	// TODO: Student writes code here

	//check roster first
	if (roster.is_enrolled(s)) {
		//remove the student from roster
		found_student = true;

		// if we dropped a student, there should be room on the roster
		update_enrollments();
	}
	else {
		int dropindex = -1;

		//check major waitlist
		dropindex = waitlist_position(MAJOR_WAITLIST, s);

		//if find the student in major waitlist
		if (dropindex != -1) {
			drop_student_from_queue(MAJOR_WAITLIST, s);
			found_student = true;
		}
		else {
			//check other waitlist
			dropindex = waitlist_position(OTHER_WAITLIST, s);

			//if find the student in other waitlist
			if (dropindex != -1) {
				drop_student_from_queue(OTHER_WAITLIST, s);
				found_student = true;
			}
		}

	}


	return found_student;
}

bool IsisCourse::drop_student_from_queue(ENROLLMENT_STATUS status, Student s) {
	bool isDropped = false;

	Queue q;

	if (status == MAJOR_WAITLIST)
		q = major_waitlist;

	if (status == OTHER_WAITLIST)
		q = other_waitlist;

	//enqueue one dummy student into this queue
	Student dummy = new Student();
	q.enqueue(dummy);

	//loop through the queue
	do {
		//get the front student
		Student frontStu = q.dequeue();

		if (frontStu.name.compare(s.name) == 0) {
			//if the student is s, do NOT enqueue it
			isDropped = true;
		}
		else {
			//if the student is not the dummy one, enqueue it
			if (frontStu.name.compare("") != 0)
				q.enqueue(frontStu);
			//if the student is the dummy one, exit the loop
			else
				break;
		}
	}
	while (1);

	return isDropped;
}

int IsisCourse::waitlist_position(ENROLLMENT_STATUS status, Student s) {
	// TODO: Student writes code here

	int stuIndex = -1;
	int index = 0;

	Queue q;

	if (status == MAJOR_WAITLIST)
		q = major_waitlist;

	if (status == OTHER_WAITLIST)
		q = other_waitlist;

	//enqueue one dummy student into this queue
	Student dummy = new Student();
	q.enqueue(dummy);

	//loop through the queue
	do {
		//get the front student
		Student frontStu = q.dequeue();

		if (frontStu.name.compare(s.name) == 0) {
			//if the student is s, do NOT enqueue it
			stuIndex = index;
		} else {
			//if the student is not the dummy one, enqueue it
			if (frontStu.name.compare("") != 0)
				q.enqueue(frontStu);
			//if the student is the dummy one, exit the loop
			else
				break;
		}

		index++;
	} while (1);

	return stuIndex;
}

IsisCourse::ENROLLMENT_STATUS IsisCourse::status(Student s) {
	// returns an ENROLLMENT_STATUS that says which list
	// (or none) that the student is on.

	// TODO: Student writes code here
}

void IsisCourse::print_list(ENROLLMENT_STATUS status) {
	Queue *waitlist_queue;
	Queue temp_queue;
	if (status == ENROLLED) {
		roster.print_class();
		return;
	}
	if (status == MAJOR_WAITLIST) {
		waitlist_queue = &major_waitlist;
	}
	else {
		waitlist_queue = &other_waitlist;
	}
	// now handle printing the queue

	// TODO: Student writes code here
}

void IsisCourse::update_enrollments() {
	// put students from the waitlists into the class
	// in priority (majors first, then others), up to
	// the class capacity.

	// TODO: Student writes code here

	while (roster.size() < class_capacity) {
		//move the major students first
		if (!major_waitlist.is_empty()) {
			//move the major student from major_waitlist
			Student pending = major_waitlist.dequeue();

			//add the major student to the roster
			roster.add(pending);
		}
		else {
			if (!other_waitlist.is_empty()) {
				//move non-major student from other_waitlist
				Student pending = other_waitlist.dequeue();

				//add the non-major student to the roster
				roster.add(pending);
			}
			else {
				//both the waitlists are empty, break the loop
				break;
			}
		}
	}
}
