// Generated by CoffeeScript 1.10.0
(function() {
  var Long, Protobuf, Uuid;

  Uuid = require('uuid');

  Protobuf = require('protobufjs');

  Long = require("../util/Long");

  module.exports = function(file) {
    var MessageProto, builder;
    builder = Protobuf.loadProtoFile(file);
    MessageProto = builder.build();
    MessageProto.file = file;
    MessageProto.reflect = builder.lookup();
    return MessageProto;
  };

}).call(this);
