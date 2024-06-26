#include "BSF_2.h"

BSF_2::BSF_2(){
   reset();
}

void BSF_2::init(double f0_, double dt_){
   set_param(f0_, dt_);
}

void BSF_2::set_param(double f0_, double dt_){
   f0 = f0_;
   dt = dt_;
   double wc = math_2pi*f0;
   double b0 = 4.0 + wc*wc*dt*dt;
   double b1 = 2.0*b0 - 16.0;
   double b2 = b0;
   double a0 = dt*dt*wc*wc + 2.0*sqrt(2.0)*dt*wc + 4.0;
   double a1 = b1;
   double a2 = dt*dt*wc*wc - 2.0*sqrt(2.0)*dt*wc + 4.0;

   lambda_1 = b0 / a0;
   lambda_2 = b1 / a0;
   lambda_3 = b2 / a0;
   lambda_4 = -a1 / a0;
   lambda_5 = -a2 / a0;
}

double BSF_2::update(double x_k){
   double y_k = 0.0;

   if (start_counter <= 1)
   {
      y_k = x_k;
      start_counter++;
   }
   else
   {
      y_k = lambda_1 * x_k + lambda_2 * x_k_1 + lambda_3 * x_k_2 + lambda_4 * y_k_1 + lambda_5 * y_k_2;
   }
   y_k_2 = y_k_1;
   y_k_1 = y_k;
   x_k_2 = x_k_1;
   x_k_1 = x_k;

   return y_k;
}

void BSF_2::reset(){
   start_counter = 0;
}

void BSF_2::set_f0(double f0_){
   set_param(f0_, dt);
}

void BSF_2::set_dt(double dt_){
   set_param(f0, dt_);
}

double BSF_2::get_f0(){
   return f0;
}

double BSF_2::get_dt(){
   return dt;
}

double BSF_2::get_fs(){
   return 1.0 / dt;
}