const { expect } = require('chai');
const lib = require('../build/Debug/lymuilib');

describe('Creating HEX from RGB', () => {
  it('Expect to create an HEX from an RGB object', () => {
    const rgb = {
      r: 5,
      g: 10,
      b: 198,
    };

    const hex = lib.getHEX(rgb);
    expect(hex).to.be.equal('#050AC6');
  });

  it('Expect to create an HEX with upper value', () => {
    const rgb = {
      r: 255,
      g: 255,
      b: 255
    };

    const hex = lib.getHEX(rgb);
    expect(hex).to.be.equal('#FFFFFF');
  });

  it('Expect to not throw when R, G, B value > uint8_t', () => {
    const rgb = {
      r: 300,
      g: 400,
      b: 1000
    };

    expect(() => lib.getHEX(rgb)).to.not.throw();
  });

  it('Expect to not throw when one of the parameters is > uint8_t', () => {
    const rgb = {
      r: 500,
      g: 10,
      b: 95
    };

    expect(() => lib.getHEX(rgb)).to.not.throw();
  });

  it('Expect to throw an error when nothing is pass to the method', () => {
    expect(() => lib.getHEX()).to.throw('Missing arguments');
  });

  it('Expect to throw when the property is not founded', () => {
    expect(() => lib.getHEX('lol')).to.throw('Property not found in JS Object');
  });

  it('Expect to throw when one of the property is missing', () => {
    const rgb = {
      r: 10,
      b: 20
    };

    expect(() => lib.getHEX(rgb)).to.throw('Property not found in JS Object');
  });

  it('Expect to throw default V8 error when null is pass', () => {
    expect(() => lib.getHEX(null)).to.throw('Cannot convert undefined or null to object');
  });
});

describe('Creating an RGB from an Hex', () => {
  it('Expect an Hex to return an RGB JS Object', () => {
    const rgb = lib.getRgbFromHex('#050AC6');

    expect(rgb).to.be.deep.equal({
      r: 5,
      g: 10,
      b: 198
    });
  });

  it('Expect a black color to return a black rgb JS Object', () => {
    const rgb = lib.getRgbFromHex('#000000');

    expect(rgb).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    });
  });

  it('Expect a white color to return a white rgb JS Object', () => {
    const rgb = lib.getRgbFromHex('#FFFFFF');
    
    expect(rgb).to.be.deep.equal({
      r: 255,
      g: 255,
      b: 255
    });
  });

  it('Expect a short hexa to not throw', () => {
    expect(() => lib.getRgbFromHex('#FF')).to.not.throw();
  });

  it('Expect a long hexa to not throw', () => {
    expect(() => lib.getRgbFromHex('#123456789ABCD')).to.not.throw();
  });

  it('Expect to throw when no param is passed', () => {
    expect(() => lib.getRgbFromHex()).to.throw('Missing arguments');
  });

  it('Expect to not throw when unknown character is pass', () => {
    const rgb = lib.getRgbFromHex('ééé');

    expect(rgb).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    });
  });
});