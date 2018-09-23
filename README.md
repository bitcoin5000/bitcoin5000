What is Bitcoin5000?
see https://bitcoin5000.org/

Coin Name: Bitcoin 5000 (BVK) Bitcoin 5000 (BVK) fork

Bitcoin 5000 (BVK) fork

Fork Block: 225000 Proof of Work: sha256 Max Block Weight: 12000000 Prefixes: 5, K, 5 premine = 0 Full blockchain size = < 7 GB

Bitcoin 5000 airdrop 9,289 000 BVK

bitcoin5000 nodes: 146.0.77.107, 5.39.221.56  (addnode 146.0.77.107 add) (addnode  5.39.221.56 add)
mining pool: 146.0.77.107 port 3032 username <bitcoin5000 adress> password: anything

Bitcoin5000Core wallet download:

windows binaries: https://github.com/bitcoin5000/bitcoin5000/blob/master/binaries/bitcoin5000-windows-setup-x86_64.exe

OSX: https://github.com/bitcoin5000/bitcoin5000/blob/master/binaries/bitcoin5000-osx-bin-x86_64.dmg

linux: https://github.com/bitcoin5000/bitcoin5000/blob/master/binaries/bitcoin5000-linux-bin-x86_64.tar.gz

License
Bitcoin5000 Core is released under the terms of the MIT license. See COPYING for more information or see https://opensource.org/licenses/MIT.

Development Process
The master branch is regularly built and tested, but is not guaranteed to be completely stable. Tags are created regularly to indicate new official, stable release versions of Bitcoin5000 Core.

The contribution workflow is described in CONTRIBUTING.md.

The developer mailing list should be used to discuss complicated or controversial changes before working on a patch set.

Developer IRC can be found on Freenode at #bitcoin5000-core-dev.

Testing
Testing and code review is the bottleneck for development; we get more pull requests than we can review and test on short notice. Please be patient and help out by testing other people's pull requests, and remember this is a security-critical project where any mistake might cost people lots of money.

Automated Testing
Developers are strongly encouraged to write unit tests for new code, and to submit new unit tests for old code. Unit tests can be compiled and run (assuming they weren't disabled in configure) with: make check. Further details on running and extending unit tests can be found in /src/test/README.md.

There are also regression and integration tests, written in Python, that are run automatically on the build server. These tests can be run (if the test dependencies are installed) with: test/functional/test_runner.py

The Travis CI system makes sure that every pull request is built for Windows, Linux, and OS X, and that unit/sanity tests are run automatically.

Manual Quality Assurance (QA) Testing
Changes should be tested by somebody other than the developer who wrote the code. This is especially important for large or high-risk changes. It is useful to add a test plan to the pull request description if testing the changes is not straightforward.
