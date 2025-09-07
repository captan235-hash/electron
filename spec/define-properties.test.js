require('ts-node/register');

const assert = require('node:assert');
const test = require('node:test');

const { defineProperties } = require('../lib/common/define-properties');

test('handles falsy default exports', () => {
  const target = {};
  defineProperties(target, [{ name: 'foo', loader: () => ({ __esModule: true, default: 0 }) }]);
  assert.strictEqual(target.foo, 0);
});
