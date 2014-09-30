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


	// if we dropped a student, there should be room on the roster
	update_enrollments();
	return found_student;
}

int IsisCourse::waitlist_position(ENROLLMENT_STATUS status, Student s) {
	// TODO: Student writes code here

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
