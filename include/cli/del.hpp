#ifndef _NAVAGRAHA_CLI_DEL_H
#define _NAVAGRAHA_CLI_DEL_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "cli_arg/process_helper.hpp"

namespace navagraha {
namespace cli {

extern char CLI_DEL_NAME[];
extern char CLI_DEL_NAMESPACE[];

class del : public cli_arg::abstract_process<del> {
private:
    cli_arg::arg<CLI_DEL_NAME, 1> name_arg;
    cli_arg::arg<CLI_DEL_NAMESPACE, 1> namespace_arg;

public:
    virtual void bind(cli_arg::process_helper<del> & helper) override;
    virtual int execute() override;
    virtual bool satisfy() const override;
};

}
}

#endif
