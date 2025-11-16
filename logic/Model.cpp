#include "Model.hpp"

Model::Model(const string& level_file_path) : board(load_level_from_file(level_file_path))
{
    compute_rules();
    send_new_state_to_controller();
}
