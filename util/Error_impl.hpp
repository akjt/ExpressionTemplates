#include <iostream>

void ErrorMsg(const std::string &file, int line, const std::string &report)
{

    std::cout << "\n\033[1mERROR:\033[0m in File " << file
              << " line no. " << line << std::endl;

    std::cout << "Error Message: " << report << std::endl;
    //      int ierr;
    //      ABORT_MPI(comm_world, ierr);
}

void ErrorMsg(const std::string &file, int line)
{
    std::cout << "\n\033[1mERROR:\033[0m in File" << file
              << " line no. " << line << std::endl;
    std::cout << "Allocation failed" << std::endl;
    //      int ierr;
    //      ABORT_MPI(comm_world, ierr);
}

/* C++20 use this ...
   void ErrorMsg( const std::string &report
                     , const std::source_location& location
                      = std::source_location::current()       )
{
   std::cout << "\n\033[1mERROR:\033[0m in File "
   << location.file_name() << "("
   << location.line() << ":"
   << location.column() << ") `"
   << location.function_name() << "` ";
   std::cout << "Error Message: " << report << '\n';
}
*/
