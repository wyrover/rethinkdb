#include "clustering/administration/http/directory_app.hpp"
#include "clustering/administration/http/issues_app.hpp"
#include "clustering/administration/http/semilattice_app.hpp"
#include "clustering/administration/http/server.hpp"
#include "http/file_app.hpp"
#include "http/http.hpp"
#include "http/routing_app.hpp"

administrative_http_server_manager_t::administrative_http_server_manager_t(
        int port,
        boost::shared_ptr<semilattice_readwrite_view_t<cluster_semilattice_metadata_t> > _semilattice_metadata, 
        clone_ptr_t<directory_rview_t<cluster_directory_metadata_t> > _directory_metadata,
        global_issue_tracker_t *_issue_tracker,
        boost::uuids::uuid _us)
{
    std::set<std::string> white_list;
    white_list.insert("/cluster.css");
    white_list.insert("/cluster.html");
    white_list.insert("/cluster-min.js");
    white_list.insert("/favicon.ico");
    white_list.insert("/js/backbone.js");
    white_list.insert("/js/bootstrap/bootstrap-alert.js");
    white_list.insert("/js/bootstrap/bootstrap-modal.js");
    white_list.insert("/js/bootstrap/bootstrap-tab.js");
    white_list.insert("/js/d3.v2.min.js");
    white_list.insert("/js/date-en-US.js");
    white_list.insert("/js/flot/jquery.flot.js");
    white_list.insert("/js/flot/jquery.flot.resize.js");
    white_list.insert("/js/handlebars-1.0.0.beta.6.js");
    white_list.insert("/js/jquery-1.7.1.min.js");
    white_list.insert("/js/jquery.form.js");
    white_list.insert("/js/jquery.hotkeys.js");
    white_list.insert("/js/jquery.sparkline.min.js");
    white_list.insert("/js/jquery.timeago.js");
    white_list.insert("/js/jquery.validate.min.js");
    white_list.insert("/js/underscore-min.js");
    white_list.insert("/images/alert-icon_small.png");
    white_list.insert("/images/information-icon_small.png");
    file_app.reset(new file_http_app_t(white_list, "../build/debug/web"));

    semilattice_app.reset(new semilattice_http_app_t(_semilattice_metadata, _directory_metadata, _us));

    directory_app.reset(new directory_http_app_t(_directory_metadata));

    issues_app.reset(new issues_http_app_t(_issue_tracker));

    std::map<std::string, http_app_t *> ajax_routes;
    ajax_routes["directory"] = directory_app.get();
    ajax_routes["issues"] = issues_app.get();
    ajax_routing_app.reset(new routing_http_app_t(semilattice_app.get(), ajax_routes));

    std::map<std::string, http_app_t *> root_routes;
    root_routes["ajax"] = ajax_routing_app.get();
    root_routing_app.reset(new routing_http_app_t(file_app.get(), root_routes));

    server.reset(new http_server_t(port, root_routing_app.get()));
}

administrative_http_server_manager_t::~administrative_http_server_manager_t() {
    /* This must be declared in the `.cc` file because the definitions of the
    destructors for the things in `boost::scoped_ptr`s are not available from
    the `.hpp` file. */
}
