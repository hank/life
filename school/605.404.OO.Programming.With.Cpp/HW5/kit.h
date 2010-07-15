// kit.h
#ifndef Kit_H
#define Kit_H
// Extremely simple Kit class
// Implements a kit that can be linked with Parts.
// This simple implementation basically just allows for setting a name
// and printing.  It could be extended later to implement more functionality.
class Kit
{
   public:
      Kit(std::string name)
      : name(name)
      {}
      
      std::string getName() const
      {
         return this->name;
      }

      void setName(const std::string& name)
      {
         this->name = name;
      }

   private:
      std::string name;
};

std::ostream& operator<< (std::ostream &stream, const Kit& kit)
{
   stream << kit.getName();

   return stream;
}
#endif // Kit_H
