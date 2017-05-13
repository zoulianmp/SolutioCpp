/******************************************************************************/
/*                                                                            */
/* Copyright 2016-2017 Steven Dolly                                           */
/*                                                                            */
/* Licensed under the Apache License, Version 2.0 (the "License");            */
/* you may not use this file except in compliance with the License.           */
/* You may obtain a copy of the License at:                                   */
/*                                                                            */
/*     http://www.apache.org/licenses/LICENSE-2.0                             */
/*                                                                            */
/* Unless required by applicable law or agreed to in writing, software        */
/* distributed under the License is distributed on an "AS IS" BASIS,          */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   */
/* See the License for the specific language governing permissions and        */
/* limitations under the License.                                             */
/*                                                                            */
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// Tasmip.hpp                                                                 //
// TASMIP Algorithm Function File                                             //
// Created September 30, 2016 (Steven Dolly)                                  //
//                                                                            //
// This function uses TASMIP to generate realistic x-ray spectra from a       //
// tungsten source, given a tube voltage (kVp) and filtration thickness of    //
// Aluminum, in mm (mmAl).                                                    //
//                                                                            //
// Publication information:                                                   //
// John M. Boone and J. Anthony Seibert, "An accurate method for              //
// computer-generating tungsten anode x-ray spectra from 30 to 140 kV",       //
// Med. Phys. 24(11), November 1997                                           //
//                                                                            //
// Data from TASMIP file (genspec1.h)                                         //
// ftp://ftp.aip.org/epaps/medical_phys/E-MPHYA-24-1661/                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// Header guards
#ifndef TASMIP_HPP
#define TASMIP_HPP

// Standard C++ header files
#include <string>
#include <vector>

// Standard C header files
#include <cmath>

// Custom headers
#include "Physics/NistPad.hpp"

namespace solutio
{
  std::vector<double> Tasmip(int tube_potential, double mm_filtration,
      std::string filter_material, std::string folder)
  {
  
    std::vector<double> spectrum;
  
    // Number of polynomial terms for each kV value
    int num_polynomial_terms[151] = {
      0,0,0,0,0,0,0,0,0,0,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
      4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
      4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,
      3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
      3,3,3,2,2,2,2,2,2,1,2,1,2,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0
    };
	
    // Polynomial coefficients for each kV value
    double polynomial_coefficients[4*151] = {
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
      -2.47098,0.0752249,0.00016013,0,
      -54.6852,2.82597,-0.0370259,0.000168545,
      -114.966,7.18167,-0.104151,0.000524694,
      -20.2312,7.52303,-0.0972592,0.000526235,
      344.016,3.17957,-0.0330693,0.000311553,
      549.329,15.0793,-0.0965665,0.000514238,
      1032.55,27.9346,-0.151778,0.000649103,
      1056.84,53.0529,0.0400621,-0.000716451,
      1098.84,82.95,0.306165,-0.00261713,
      495.798,147.004,-0.110282,-0.00135451,
      -143.783,222.91,-0.620631,0.000189685,
      -1106.66,277.05,-0.574362,-0.00106621,
      -2281.77,342.442,-0.579332,-0.00230358,
      -5591.72,472.413,-1.42996,0.000504908,
      -9340.54,618.637,-2.40787,0.00370171,
      -14065,776.049,-3.4304,0.00664641,
      -19203.2,941.867,-4.54481,0.00992016,
      -25159.5,1130.91,-5.99764,0.0144155,
      -31519.3,1331.12,-7.55688,0.019258,
      -31659.4,1293.12,-6.62524,0.0159367,
      -31977,1259.43,-5.72172,0.0126961,
      -31502,1213.02,-4.9954,0.0106863,
      -34045.4,1273.28,-5.44075,0.0127505,
      -35257.5,1267.17,-5.05259,0.0114025,
      -36598,1264.49,-4.69822,0.0101743,
      -39355.2,1325.72,-5.26013,0.0125117,
      -42394.5,1396.68,-5.96159,0.0153918,
      -45054.8,1445.3,-6.32455,0.0165782,
      -48074.4,1506.53,-6.84101,0.0183228,
      -47721.8,1455.01,-6.18372,0.0160985,
      -46872.6,1383.59,-5.29642,0.0130534,
      -45340,1304.46,-4.45863,0.0102913,
      -47296.7,1337.3,-4.76811,0.0112984,
      -45921.6,1239.85,-3.6517,0.00750512,
      -44176.2,1131.55,-2.4227,0.00334071,
      -49753.2,1307.91,-4.4909,0.0109328,
      -56131.9,1511.97,-6.8753,0.0196294,
      -55240.7,1421.87,-5.66911,0.0148764,
      -54499.4,1337.32,-4.52793,0.0103572,
      -58841.9,1478.83,-6.29327,0.0168762,
      -63109.8,1616.22,-8.00933,0.0232159,
      -59955.9,1496.68,-6.90603,0.0197785,
      -59641,1456.7,-6.53432,0.0185367,
      -61325.5,1489.14,-6.9568,0.0200507,
      -63048.9,1522.43,-7.39089,0.0216112,
      -59943.4,1380.87,-5.83974,0.0161994,
      -56108.7,1218.27,-4.0921,0.0101841,
      -18257.3,-138.212,9.55782,-0.0214005,
      22200.2,-1568.66,23.8981,-0.0550569,
      55017.1,-2721.16,35.278,-0.080474,
      89229.4,-3915.85,47.0499,-0.107056,
      21049.9,-1557.36,23.2189,-0.0513497,
      -50765.2,903.221,-1.57983,0.0073063,
      -60307.9,1202.07,-4.55231,0.0141953,
      -69849.9,1499.85,-7.51309,0.021038,
      -71086.4,1507.31,-7.47214,0.020248,
      -73275.4,1540.89,-7.68993,0.0202855,
      -31611.8,129.777,6.39248,-0.0169374,
      10363,-1288.01,20.5198,-0.054239,
      -41324.9,442.09,2.4486,2.20225e-05,
      -99831.4,2351.14,-17.2219,0.0589682,
      -83458.3,1820.26,-11.4076,0.0347451,
      -60380.5,1099.14,-3.83639,0.00521521,
      -73322.3,1472.74,-7.48113,0.0164473,
      -88668.9,1911.74,-11.7274,0.029487,
      -89062.8,1903.69,-11.6664,0.0295337,
      -91220.8,1949.91,-12.124,0.0311903,
      -91959.2,1956.64,-12.2202,0.0315568,
      -93935,1997.57,-12.6445,0.0329425,
      -94605.9,1985.57,-12.4063,0.0318846,
      -94659.1,1947.31,-11.9191,0.0300554,
      -105496,2287.74,-15.4656,0.0419277,
      -112882,2523.28,-18.0638,0.0509944,
      -56523.8,846.081,-1.8903,0,
      -62531.1,954.621,-2.42146,0,
      -60632.5,909.326,-2.22283,0,
      -58390.9,858.149,-1.99938,0,
      -61774.4,909.695,-2.21962,0,
      -65513.4,967.438,-2.46616,0,
      -64821.1,946.375,-2.38406,0,
      -63965.9,922.536,-2.29053,0,
      -59763.8,838.469,-1.91813,0,
      -54832.4,741.841,-1.49268,0,
      -55459.1,739.222,-1.46675,0,
      -51918.7,667.713,-1.15944,0,
      -53372.6,686.444,-1.24856,0,
      -54997.1,708.082,-1.34986,0,
      -61098.6,810.304,-1.80524,0,
      -67803.1,922.439,-2.30102,0,
      -64635.7,853.616,-1.98054,0,
      -61423.2,784.198,-1.65825,0,
      -65425.7,855.126,-1.99914,0,
      -68502.2,910.44,-2.27525,0,
      -67751.8,873.305,-2.05065,0,
      -56709.9,671.731,-1.17464,0,
      -64311.6,798.217,-1.73021,0,
      -72847.8,939.704,-2.34536,0,
      -72963.7,937.042,-2.34909,0,
      -72519.7,925.69,-2.31858,0,
      -73737.9,938.756,-2.37174,0,
      -75221.4,955.706,-2.44056,0,
      -66450.1,812.994,-1.89208,0,
      -53917.2,611.114,-1.1108,0,
      -69501.1,838.185,-1.94384,0,
      -76568.4,934.029,-2.2728,0,
      -71698.2,856.269,-1.99406,0,
      -63076.5,719.95,-1.49034,0,
      -68961,801.466,-1.78594,0,
      -79488,954.546,-2.35645,0,
      -80389.4,960.394,-2.36806,0,
      -81865.5,974.475,-2.41113,0,
      -81272.3,978.439,-2.50146,0,
      -64478.5,732.755,-1.63899,0,
      -38069.8,313.166,0,0,
      -37978.1,310.109,0,0,
      -40233.9,325.521,0,0,
      -42809.4,343.283,0,0,
      -41146.7,327.276,0,0,
      -39259.7,309.655,0,0,
      319.165,0,0,0,
      -44258,342.54,0,0,
      81.1561,0,0,0,
      -38679.9,296.981,0,0,
      1306.71,0,0,0,
      1153.42,0,0,0,
      981.706,0,0,0,
      809.966,0,0,0,
      668.884,0,0,0,
      527.781,0,0,0,
      349.834,0,0,0,
      171.861,0,0,0,
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
    };

    // Aluminum attenuation data, from NIST database
    NistPad NistAl(folder, filter_material);
	
    // Generate spectrum for selected kVp value and Al thickness
    double energy, sum, mu, attenuation;
    for(int n = 0; n < 151; n++){
      if( (num_polynomial_terms[n] == 0) || (n >= tube_potential) ){
        spectrum.push_back(0.0);
        continue;
      }
      else {
        // Calculate attenuation by filtration
        energy = double(n) / 1000.0;
        mu = NistAl.LinearAttenuation(energy);
        attenuation = exp(-mu*mm_filtration*0.1);

        // Calculate spectrum using TASMIP polynomials and apply filtration
        sum = 0.0;
        for(int t = 0; t < num_polynomial_terms[n]; t++){
          sum += (polynomial_coefficients[(4*n+t)] * pow(tube_potential,t));
        }
        spectrum.push_back(sum*attenuation);
      }
    }

    // Normalize spectrum
    sum = 0.0;
    for(int n = 0; n < 150; n++) sum += (spectrum[n] + spectrum[(n+1)]) / 2.0;
    for(int n = 0; n < 151; n++) spectrum[n] /= sum;
    
    return spectrum;
  }
}

// End header guard
#endif
