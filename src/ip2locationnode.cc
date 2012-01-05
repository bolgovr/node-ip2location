#include <v8.h>
#include <node.h>
#include <IP2Location.h>
#include <string>
using namespace node;
using namespace v8;


class Location: ObjectWrap
{
    public:
        IP2Location *ipdb;
        static Persistent<FunctionTemplate> s_ct;
        static void Init(Handle<Object> target)
        {
            HandleScope scope;
            Local<FunctionTemplate> t = FunctionTemplate::New(New);
            s_ct = Persistent<FunctionTemplate>::New(t);
            s_ct->InstanceTemplate()->SetInternalFieldCount(1);
            s_ct->SetClassName(String::NewSymbol("Location"));

            NODE_SET_PROTOTYPE_METHOD(s_ct,"getIpInfo", GetIpInfo);
            NODE_SET_PROTOTYPE_METHOD(s_ct,"close",close);



            target->Set(String::NewSymbol("Location"),s_ct->GetFunction());
        }
        Location()
        {

        }

        ~Location()
        {
        }


        void Close()
        {
            HandleScope scope;    
            if(ipdb!=NULL){
                IP2Location_close(ipdb);
                ipdb=NULL;
            }
        }
        static Handle<Value> New(const Arguments& args)
        {
            HandleScope scope;
            Location* location = new Location();
            String::Utf8Value dbpath(args[0]->ToString());
            location->ipdb = IP2Location_open(*dbpath);
            location->Wrap(args.This());
            return args.This();

        }


        static Handle<Value> close(const Arguments& args){
            HandleScope scope;
            Location* location = ObjectWrap::Unwrap<Location>(args.This());
            location->Close();
            return Undefined(); 
        }
        static Handle<Value> GetIpInfo(const Arguments& args)
        {
            HandleScope scope;
            String::Utf8Value query(args[0]->ToString());
            Location *location = ObjectWrap::Unwrap<Location>(args.This());
            if(!location->ipdb){
                return ThrowException(Exception::TypeError(String::New("connection already closed")));
            }
            IP2LocationRecord *record = IP2Location_get_all(location->ipdb,*query);
            Local<Object> result = Object::New();
            if(record->country_short!=NULL){
                result->Set(
                        String::New("country_short"),
                        String::New(record->country_short)
                        );
            }
            if(record->country_long!=NULL){
                result->Set(
                        String::New("country_long"),
                        String::New(record->country_long)
                        );
            }
            if(record->region != NULL){
                result->Set(
                        String::New("region"),
                        String::New(record->region)

                        );
            }
            if(record->city != NULL){
                result->Set(
                        String::New("city"),
                        String::New(record->city)
                        );
            }
            if(record->timezone != NULL){
                result->Set(
                        String::New("timezone"),
                        String::New(record->timezone)

                        );
            }
            IP2Location_free_record(record);
            return result;
        }
};

Persistent<FunctionTemplate> Location::s_ct;

extern "C" {
    static void init(Handle<Object> target)
    {
        Location::Init(target);
    }
    NODE_MODULE(ip2locationnode,init);
}

