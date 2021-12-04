#pragma once


#define METHOD_FILES_DIR "/tmp/"





class ExperimentHandler : public CivetHandler
{
public:
    bool handleGet(CivetServer* server, struct mg_connection* conn);
    bool handlePost(CivetServer* server, struct mg_connection* conn);
    bool handlePut(CivetServer* server, struct mg_connection* conn);
};

class ExitHandler : public CivetHandler
{
public:
    bool handleGet(CivetServer* server, struct mg_connection* conn);
};



class MethodfileHandler : public CivetHandler
{
public:
    bool handleGet(CivetServer* server, struct mg_connection* conn);
    bool handlePost(CivetServer* server, struct mg_connection* conn);
    bool handlePut(CivetServer* server, struct mg_connection* conn);
};

