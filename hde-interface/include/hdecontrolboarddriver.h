/*
 * Copyright (c) 2018, <copyright holder> <email>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY <copyright holder> <email> ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> <email> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef HDEDRIVER_H
#define HDEDRIVER_H

#include <iostream>
#include <string>
#include <vector>
#include <yarp/os/LogStream.h>
#include <yarp/dev/DeviceDriver.h>
#include <yarp/dev/IAnalogSensor.h>
#include <yarp/os/Semaphore.h>
#include <yarp/dev/IEncoders.h>

namespace yarp
{
    namespace dev
    {
        class HDEDriver;
    }
}

extern const unsigned ForceTorqueChannelsNumber;

class yarp::dev::HDEDriver:
    public yarp::dev::DeviceDriver,
    public yarp::dev::IAnalogSensor,
    public yarp::dev::IEncoders
{
    
private:
    
    int number_of_sensors;
    int number_of_channels;
    
    yarp::sig::Vector force_torque_vector;
    std::vector<std::string> ft_frame_names;

    yarp::os::Semaphore data_mutex;
    
    yarp::sig::Vector joint_zero_positions;
    yarp::sig::Vector joint_positions;
    yarp::sig::Vector joint_velocities;
    
public:
    
    HDEDriver();
    virtual ~HDEDriver();
        
    //Device Driver
    virtual bool open(yarp::os::Searchable& config);
    virtual bool close();
    
    //Analog Sensor
    virtual int read(yarp::sig::Vector& out);
    virtual int getState(int channel);
    virtual int getChannels();
    virtual int calibrateChannel(int channel,double v);
    virtual int calibrateSensor();
    virtual int calibrateSensor(const yarp::sig::Vector& value);
    virtual int calibrateChannel(int channel);
    
    int getTotalSensorsSize();
    std::string getFTFrameName(int& i);
    void setFTValues(double u,int pos);
    
    //Encoders
    virtual bool getAxes(int *ax);
    virtual bool getEncoder(int j, double* v);
    virtual bool getEncoders(double* encs);
    virtual bool resetEncoder(int j);
    virtual bool resetEncoders();
    virtual bool setEncoder(int j, double val);
    virtual bool setEncoders(const double* vals);
    virtual bool getEncoderSpeed(int j, double* sp);
    virtual bool getEncoderSpeeds(double* spds);
    virtual bool getEncoderAcceleration(int j, double* spds);
    virtual bool getEncoderAccelerations(double* accs);

    
};

#endif // HDEDRIVER_H