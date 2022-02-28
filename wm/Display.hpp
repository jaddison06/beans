#include "V2.hpp"
#include "Colour.hpp"

namespace beans {
    class Display {
        public:
            virtual V2 GetSize() = 0;

            virtual void Destroy() = 0;
            virtual void Flush() = 0;

            virtual void SetClip(V2 pos, V2 size) = 0;
            virtual void ResetClip() = 0;

            virtual void DrawPoint(V2 pos, Colour col) = 0;
            virtual void DrawLine(V2 a, V2 b, beans::Colour col) = 0;
            virtual void DrawRect(V2 pos, V2 size, Colour col) = 0;
            virtual void FillRect(V2 pos, V2 size, Colour col) = 0;
            virtual void DrawCircle(V2 pos, int radius, Colour col) = 0;
            virtual void FillCircle(V2 pos, int radius, Colour col) = 0;
    };
}