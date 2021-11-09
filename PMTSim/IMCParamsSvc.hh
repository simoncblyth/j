#ifndef IMCParamsSvc_hh
#define IMCParamsSvc_hh

/*
 * IMCParamsSvc allows user to *query* parameters in following ways:
 *
 *   IMCParamsSvc* svc = ...;
 *
 *   vector< tuple<double, double> > props;
 *   svc->Get("Material.LS.RINDEX", props);
 *
 *   vector< tuple<string, double> > props;
 *   svc->Get("Material.LS.Elements", props);
 *
 * Note, the order could be important, so vector is used in the interface.
 *
 * But sometimes, user could put several (key,value) pairs in file, 
 * so we also support map.
 *
 *   map<string, double> props;
 *   svc->Get("Material.LS.scale", props);
 * 
 * The implemenation could be based on files or database.
 * We only keep this interface easy to understand.
 */

#include <vector>
#include <map>
#include <boost/tuple/tuple.hpp>

class IMCParamsSvc {
    public:
        virtual ~IMCParamsSvc() {}

        typedef boost::tuple<double, double> elem_d2d; // double, double
        typedef boost::tuple<std::string, double> elem_s2d; // string, double

        typedef std::vector<elem_d2d> vec_d2d;
        typedef std::vector<elem_s2d> vec_s2d;
        // Instead of using (string: double) vector, we could also use map<string, double>.
        typedef std::map<std::string, double> map_s2d;

        virtual bool Get(const std::string& param, vec_d2d& props) = 0;
        virtual bool Get(const std::string& param, vec_s2d& props) = 0;
        virtual bool Get(const std::string& param, map_s2d& props) = 0;

};

#endif
