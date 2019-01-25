//-------------------------------------------------------------------------//
//                                                                         //
//  This benchmark is an OpenCL version of the NPB BT code for multiple    //
//  devices. This OpenCL version is developed by the Center for Manycore   //
//  Programming at Seoul National University and derived from the MPI      //
//  Fortran versions in "NPB3.3-MPI" developed by NAS.                     //
//                                                                         //
//  Permission to use, copy, distribute and modify this software for any   //
//  purpose with or without fee is hereby granted. This software is        //
//  provided "as is" without express or implied warranty.                  //
//                                                                         //
//  Information on NPB 3.3, including the technical report, the original   //
//  specifications, source code, results and information on how to submit  //
//  new results, is available at:                                          //
//                                                                         //
//           http://www.nas.nasa.gov/Software/NPB/                         //
//                                                                         //
//  Send comments or suggestions for this OpenCL version to                //
//  cmp@aces.snu.ac.kr                                                     //
//                                                                         //
//          Center for Manycore Programming                                //
//          School of Computer Science and Engineering                     //
//          Seoul National University                                      //
//          Seoul 151-744, Korea                                           //
//                                                                         //
//          E-mail:  cmp@aces.snu.ac.kr                                    //
//                                                                         //
//-------------------------------------------------------------------------//

//-------------------------------------------------------------------------//
// Authors: Sangmin Seo, Jungwon Kim, Jun Lee, Gangwon Jo, Jeongho Nah,    //
//          and Jaejin Lee                                                 //
//-------------------------------------------------------------------------//

#ifndef __BT_DIM_H__
#define __BT_DIM_H__

#define COPY_FACES_OUT1_DIM_CPU   3
#define COPY_FACES_OUT2_DIM_CPU   3
#define COPY_FACES_OUT3_DIM_CPU   3
#define COPY_FACES_IN1_DIM_CPU    3
#define COPY_FACES_IN2_DIM_CPU    3
#define COPY_FACES_IN3_DIM_CPU    3
#define COMPUTE_RHS1_DIM_CPU      3
#define COMPUTE_RHS2_DIM_CPU      3
#define COMPUTE_RHS6_DIM_CPU      3
#define X_SOLVE_DIM_CPU           1
#define Y_SOLVE_DIM_CPU           1
#define Z_SOLVE_DIM_CPU           1
#define ADD_DIM_CPU               3

#define COPY_FACES_OUT1_DIM_GPU   3
#define COPY_FACES_OUT2_DIM_GPU   3
#define COPY_FACES_OUT3_DIM_GPU   3
#define COPY_FACES_IN1_DIM_GPU    3
#define COPY_FACES_IN2_DIM_GPU    3
#define COPY_FACES_IN3_DIM_GPU    3
#define COMPUTE_RHS1_DIM_GPU      3
#define COMPUTE_RHS2_DIM_GPU      3
#define COMPUTE_RHS6_DIM_GPU      3
#define X_SOLVE_DIM_GPU           2
#define Y_SOLVE_DIM_GPU           2
#define Z_SOLVE_DIM_GPU           2
#define ADD_DIM_GPU               3

#endif //__BT_DIM_H__

