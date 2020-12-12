#!/bin/bash
find . -type f -exec sed -i -e 's/\/RadixLiteral\/RadixLiteral\.h/\/RadixLiteral\/src\/RadixLiteral\.h/g' {} +
