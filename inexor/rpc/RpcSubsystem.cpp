

#include "inexor/rpc/RpcSubsystem.hpp"
#include "inexor/util/Logging.hpp"
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "inexor/rpc/inexor_service.grpc.pb.h"
#include "inexor/rpc/inexor_service.pb.h"


using namespace inexor::util;
SUBSYSTEM_REGISTER(rpc, inexor::rpc::RpcSubsystem);


using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::CompletionQueue;
using grpc::ClientAsyncResponseReader;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

namespace inexor {
namespace rpc {

class GreeterClient
{
private:
    // Out of the passed in Channel comes the stub, stored here, our view of the
    // server's exposed services.
    std::unique_ptr<Greeter::Stub> stub_;
public:
    GreeterClient(std::shared_ptr<Channel> channel)
        : stub_(Greeter::NewStub(channel))
    {
    }

    // Assambles the client's payload, sends it and presents the response back from the server.
    std::string SayHello(const std::string &user)
    {
        // Data we are sending to the server.
        HelloRequest request;
        request.set_name(user);

        // Container for the data we expect from the server.
        HelloReply reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context;

        // The producer-consumer queue we use to communicate asynchronously with the
        // gRPC runtime.
        CompletionQueue cq;

        // Storage for the status of the RPC upon completion.
        Status status;

        // stub_->AsyncSayHello() perform the RPC call, returning an instance we
        // store in "rpc". Because we are using the asynchronous API, we need the
        // hold on to the "rpc" instance in order to get updates on the ongoig RPC.
        std::unique_ptr<ClientAsyncResponseReader<HelloReply> > rpc(
            stub_->AsyncSayHello(&context, request, &cq));

        // Request that, upon completion of the RPC, "reply" be updated with the
        // server's response; "status" with the indication of whether the operation
        // was successful. Tag the request with the integer 1.
        rpc->Finish(&reply, &status, (void*)1);
        void* got_tag;
        bool ok = false;
        // Block until the next result is available in the completion queue "cq".
        cq.Next(&got_tag, &ok);

        // Verify that the result from "cq" corresponds, by its tag, our previous request.
        GPR_ASSERT(got_tag == (void*)1);
        // ... and that the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        // Act upon the status of the actual RPC.
        if(status.ok()) return reply.message();
        else            return "RPC failed";
    }
};

void testclientrpc()
{
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint (in this case,
    // localhost at port 50051). We indicate that the channel isn't authenticated
    // (use of InsecureChannelCredentials()).
    GreeterClient greeter(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    std::string user("world");
    std::string reply = greeter.SayHello(user);  // The actual RPC call!
    spdlog::get("global")->info() << "Greeter received: "; // << reply;

}

}
}
