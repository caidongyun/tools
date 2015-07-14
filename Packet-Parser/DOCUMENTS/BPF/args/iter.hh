//iter.hh
//Written by, Sohail Qayum Malik<sohail@stupidcomputing.com>

#include <iterator>

template <class T>
class iter : public iterator< random_access_iterator_tag, iter<T> > {

   T* container; 

   public:

      typedef	typename	T::size_type        size_type;

      iter(T* container) : container(container) {
      }

      // Iterator type specific services

      //Post increment
      bool operator++(int) {
	 return (*container)++;     
      }	
      //Pre increment
      bool operator++(void) {
	 return ++(*container);
      }
      //Pre decrement
      bool operator--(void) {
         return --(*container);
      }

      //Subscript operator
      bool operator[](int command) {
         return (*container)[command]; 	      
      }
      //Value of/at operator
      string operator*(void) {
	 return *(*container);     
      }

      size_type size(void) {
	 return container->size();      
      } 	      

     //all User defined services 

      bool push(void) {
	 return container->push();     
      }
      
      bool pop(void) {
	 return container->pop();     
      }
      
      bool discard(void) {
         return container->discard();
      }
     

};	
