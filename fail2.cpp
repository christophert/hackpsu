// Copyright (C) 2013-2014 Thalmic Labs Inc.
// Distributed under the Myo SDK license agreement. See LICENSE.txt for details.

// This sample illustrates how to use EMG data. EMG streaming is only supported for one Myo at a time.

#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>


#include <myo/myo.hpp>
#include <cpprest/json.h>
#include <cpprest/http_client.h>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

//using namespace web;

class DataCollector : public myo::DeviceListener {
public:
	DataCollector()
		: emgSamples()
	{
	}

	// onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
	void onUnpair(myo::Myo* myo, uint64_t timestamp)
	{
		// We've lost a Myo.
		// Let's clean up some leftover state.
		emgSamples.fill(0);
	}

	// onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enabled.
	void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
	{
		for (int i = 0; i < 8; i++) {
			emgSamples[i] = emg[i];
		}
	}

	// There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
	// For this example, the functions overridden above are sufficient.

	// We define this function to print the current values that were updated by the on...() functions above.
	std::string getData()
	{
		// Clear the current line
		//        std::cout << '\r';

		// Print out the EMG data.
		std::stringstream rss;
		std::string ress;
		for (size_t i = 0; i < emgSamples.size(); i++) {
			cout << "source " << static_cast<int>(emgSamples[i]) << endl;
			std::ostringstream oss;
			oss << static_cast<int>(emgSamples[i]);
			std::string emgString = oss.str();

			rss << emgString << 4 - emgString.size();
			if (i != emgSamples.size() - 1) {
				rss << ",";
			}
		}
		ress = rss.str();
		return ress;
		//return emgSamples;
	}

	std::array<int, 8> dataInArray()
	{
		array<int, 8> retArray;
		for (size_t i = 0; i<emgSamples.size(); i++) {
			int current = static_cast<int>(emgSamples[i]);
			retArray[i] = current;
		}
		return retArray;
	}

	std::float_t getAverages(array<int, 8> inarr)
	{
		std::float_t avg = 0;
		for (size_t i = 0; i<inarr.size(); i++) {
			avg += inarr[i];
		}
		avg /= inarr.size();
		return avg;
	}

	// The values of this array is set by onEmgData() above.
	std::array<int8_t, 8> emgSamples;
};



int main(int argc, char** argv)
{
	// We catch any exceptions that might occur below -- see the catch statement for more details.
	try {

		// First, we create a Hub with our application identifier. Be sure not to use the com.example namespace when
		// publishing your application. The Hub provides access to one or more Myos.
		myo::Hub hub("us.tranit.LocalApp");

		std::cout << "Attempting to find a Myo..." << std::endl;

		// Next, we attempt to find a Myo to use. If a Myo is already paired in Myo Connect, this will return that Myo
		// immediately.
		// waitForMyo() takes a timeout value in milliseconds. In this case we will try to find a Myo for 10 seconds, and
		// if that fails, the function will return a null pointer.
		myo::Myo* myo = hub.waitForMyo(10000);

		// If waitForMyo() returned a null pointer, we failed to find a Myo, so exit with an error message.
		if (!myo) {
			throw std::runtime_error("Unable to find a Myo!");
		}

		// We've found a Myo.
		std::cout << "Connected to a Myo armband!" << std::endl << std::endl;

		// Next we enable EMG streaming on the found Myo.
		myo->setStreamEmg(myo::Myo::streamEmgEnabled);

		// Next we construct an instance of our DeviceListener, so that we can register it with the Hub.
		DataCollector collector;

		// Hub::addListener() takes the address of any object whose class inherits from DeviceListener, and will cause
		// Hub::run() to send events to all registered device listeners.
		hub.addListener(&collector);

		// Finally we enter our main loop.
		bool loopRun = true;
		int counter = 0;
		const int max = 100;
		array<float, max> avgArray;
		while (loopRun) {
			std::string tenSampleString;
			std::stringstream tenSampleStream;
			hub.run(1000 / 50);
			array<int, 8> array = collector.dataInArray();

			if (counter < max) {
				avgArray[counter] = collector.getAverages(array);
				counter++;
			}


			
			else {
				//post data here
				std::wstringstream samplestream;
				for (size_t i = 0; i < avgArray.size(); i++) {
					if (i < avgArray.size() - 1) {
						samplestream << avgArray[i] << ',';
					}
					else {
						samplestream << avgArray[i];
					}
				}
				std::wstring sample = samplestream.str();

				http_client client(L"http://myownlife-hpsu1.cloudapp.net");

				uri_builder uri(L"/interp.php");
				uri.append_query(L"u", sample);
				client.request(methods::GET, uri.to_string());


				//debug print
				cout << '[';
				for (size_t i = 0; i<avgArray.size(); i++) {
					cout << avgArray[i] << ',';
				}
				cout << ']' << "counter: " << counter << endl;
				counter = 0;
				avgArray.fill(0);
			}

			//            cout << '[';
			//            for(size_t i = 0; i<array.size();i++) {
			//                cout << array[i] << ',';
			//            }
			//            cout << ']' << "Avg: " << collector.getAverages(array) << endl;

			//std::cout << std::to_string(collector.getAverages()) << "\n";
		}

		// If a standard exception occurred, we print out its message and exit.
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::cerr << "Press enter to continue.";
		std::cin.ignore();
		return 1;
	}
}
