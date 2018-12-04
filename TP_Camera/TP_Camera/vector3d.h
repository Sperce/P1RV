//
//  vector3D.h
// 


#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
using namespace std;

class Vector3D
{
private:
   double vX;
   double vY;
   double vZ;
public:
   Vector3D();
   Vector3D(double x,double y,double z);
   Vector3D(const Vector3D & v);
   Vector3D(const Vector3D & from,const Vector3D & to);
   
   Vector3D & operator= (const Vector3D & v);
   
   Vector3D & operator+= (const Vector3D & v);
   Vector3D operator+ (const Vector3D & v) const;
   
   Vector3D & operator-= (const Vector3D & v);
   Vector3D operator- (const Vector3D & v) const;
   
   Vector3D & operator*= (const double a);
   Vector3D operator* (const double a)const;
   friend Vector3D operator* (const double a,const Vector3D & v);
   
   Vector3D & operator/= (const double a);
   Vector3D operator/ (const double a)const;
   
   // Setters/Getters
   void setVx(double x);
   double getVx();
   
   void setVy(double y);
   double getVy();
   
   void setVz(double z);
   double getVz();
   
   Vector3D crossProduct(const Vector3D & v)const;
   double length()const;
   Vector3D & normalize();
   
   friend ostream& operator<<(ostream& os, Vector3D const & v) {
      return os << "("<<v.vX<<","<<v.vY<<","<<v.vZ<<")" << endl;
   }
};

#endif //VECTOR3D_H
