#include "layout.hpp"
#include "svgout.hpp"

struct Box {
public:
        int width(){return 16;}
        int height(){return 16;}
        void bounds(const zw::layout::bounds_type& b)
        {
                bounds_ = b;
        }

        void accept(svgout& out)
        {
                out.rect(bounds_.x0(),bounds_.y0(),bounds_.w(),bounds_.h(),"blue");
        }

        zw::layout::bounds_type bounds_;
};

struct Box2 {
public:
        int width(){return zw::layout::infinity();}
        int height(){return zw::layout::infinity();}
        void bounds(const zw::layout::bounds_type& b)
        {
                bounds_ = b;
                std::cout << "b " << b.w() << "," << b.h() << std::endl;
        }

        void accept(svgout& out)
        {
                out.rect(bounds_.x0(),bounds_.y0(),bounds_.w(),bounds_.h(),"blue","black");
        }

        zw::layout::bounds_type bounds_;
};


int main(int argc,char** argv)
{
        Box b1,b2,b3,b4;
        Box2 b5;

        zw::layout::hbox i(32,48);
        i << zw::layout::frame<svgout>(b3)
          << zw::layout::frame<svgout>(b4);

        zw::layout::vbox o(64,64);
        o << zw::layout::frame<svgout>(b1)
          << zw::layout::frame<svgout>(b2)
          << i;
        
        zw::layout::layer shell(256,256);
        zw::layout::layer shell2;
        shell2 << zw::layout::frame<svgout>(b5) << o ;
        shell << shell2;
        
        svgout out("t.svg",256,256);

        shell.layout(zw::layout::bounds_type(0,0,256,256));
        shell.accept(out);
}
