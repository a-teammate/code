// Generated by CoffeeScript 1.10.0
(function() {
  var BasicLong, Long,
    bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    extend = function(child, parent) { for (var key in parent) { if (hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor(); child.__super__ = parent.prototype; return child; },
    hasProp = {}.hasOwnProperty,
    slice = [].slice;

  BasicLong = require('long');

  Long = (function(superClass) {
    extend(Long, superClass);

    function Long() {
      this.toBufferBE = bind(this.toBufferBE, this);
      this.toBufferLE = bind(this.toBufferLE, this);
      this.writeToBufferBE = bind(this.writeToBufferBE, this);
      this.writeToBufferLE = bind(this.writeToBufferLE, this);
      return Long.__super__.constructor.apply(this, arguments);
    }

    Long.fromBufferLE = function(buf) {
      return new Long(buf.readUInt32LE(0), buf.readUInt32LE(4), true);
    };

    Long.fromBufferBE = function(buf) {
      return new Long(buf.readUInt32BE(4), buf.readUInt32BE(0), true);
    };

    Long.fromObj = function(o) {
      return Long.fromBits(o.low, o.high, o.unsigned);
    };

    Long.fromBits = function() {
      var a;
      a = 1 <= arguments.length ? slice.call(arguments, 0) : [];
      return new Long(Long.__super__.constructor.fromBits.apply(this, a));
    };

    Long.fromInt = function() {
      var a;
      a = 1 <= arguments.length ? slice.call(arguments, 0) : [];
      return new Long(Long.__super__.constructor.fromInt.apply(this, a));
    };

    Long.fromNumber = function() {
      var a;
      a = 1 <= arguments.length ? slice.call(arguments, 0) : [];
      return new Long(Long.__super__.constructor.fromNumber.apply(this, a));
    };

    Long.fromString = function() {
      var a;
      a = 1 <= arguments.length ? slice.call(arguments, 0) : [];
      return new Long(Long.__super__.constructor.fromString.apply(this, a));
    };

    Long.fromValue = function() {
      var a;
      a = 1 <= arguments.length ? slice.call(arguments, 0) : [];
      return new Long(Long.__super__.constructor.fromValue.apply(this, a));
    };

    Long.prototype.writeToBufferLE = function(b, ofs) {
      if (ofs == null) {
        ofs = 0;
      }
      b.writeUInt32LE(this.low, 0 + ofs);
      b.writeUInt32LE(this.high, 4 + ofs);
      return b;
    };

    Long.prototype.writeToBufferBE = function(b, ofs) {
      if (ofs == null) {
        ofs = 0;
      }
      b.writeUInt32BE(this.high, 0 + ofs);
      b.writeUInt32BE(this.low, 4 + ofs);
      return b;
    };

    Long.prototype.toBufferLE = function() {
      return this.writeToBufferLE(new Buffer(8));
    };

    Long.prototype.toBufferBE = function() {
      return this.writeToBufferBE(new Buffer(8));
    };

    return Long;

  })(BasicLong);

  module.exports = Long;

}).call(this);
