#include <iostream>
#include "App.hpp"
#include "utils/errors/Exception.hpp"

int main()
{
    try
    {
        App app;
        app.run();
    }
    catch (const ShaderException& e)
    {
        std::cerr << "ShaderException: " << e.what() << std::endl;
        return -1;
    }
    catch (const std::string& e)
    {
        std::cerr << "Exception: " << e << std::endl;
        return -1;
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return -1;
    }
    catch (...)
    {
        std::cerr << "Unknown exception" << std::endl;
        return -1;
    }

    return 0;
}