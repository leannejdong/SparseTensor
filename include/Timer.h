/*!
 * Created by leanne on 1/26/21.
 */

#ifndef SPARSETENSOR_TIMER_H
#define SPARSETENSOR_TIMER_H

#include <chrono>
#include <cassert>

using std::cerr;

namespace SparseTensor{
    struct Timer
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
        std::chrono::duration<float> duration;

        Timer()
        {
            start = std::chrono::high_resolution_clock::now();
        }
        ~Timer()
        {
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;

            float ms = duration.count() * 1000.0f;
            float s = duration.count();
            //  std::cerr << "Timer took in ms " << ms << "ms" << "\n";
            std::cerr << "Timer took in s " << s << "s" << "\n";

        }
    };
}


#endif //SPARSETENSOR_TIMER_H
