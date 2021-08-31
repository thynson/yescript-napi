module.exports = {
  testRegex: '(/__tests__/.*|\\.(test|spec|e2e-spec|e2e-test))\\.(ts|tsx|js)$',
  coveragePathIgnorePatterns: ['/node_modules/', '/test/', '/tools/'],
  coverageThreshold: {
    global: {
      lines: 80,
      statements: 80,
    },
  },
  collectCoverage: true,
}
