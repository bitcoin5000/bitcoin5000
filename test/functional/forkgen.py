#!/usr/bin/env python3
# Copyright (c) 2014-2016 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
"""Test forkgen cases."""

import time
import json
from test_framework.test_framework import Bitcoin5000TestFramework
from test_framework.util import *

class ForkGenTest(Bitcoin5000TestFramework):
    def set_test_params(self):
        self.setup_clean_chain = True
        self.num_nodes = 4
        self.extra_args = [["-disablefork"], ["-disablefork"], [], []]

    # def add_options(self, parser):
    #     parser.add_option("--mineblock", dest="mine_block", default=False, action="store_true",
    #                       help="Test double-spend of 1-confirmed transaction")

    # def setup_network(self):
    #     # Start with split network:
    #     super().setup_network()
    #     disconnect_nodes(self.nodes[1], 2)
    #     disconnect_nodes(self.nodes[2], 1)

    def run_test(self):
        # Connect everyone
        for i in range(4):
            for j in range(4):
                connect_nodes(self.nodes[i], j)

        # All nodes should start with 0 BVK.
        # They should be connected
        starting_balance = 0
        for i in range(4):
            print(i, self.nodes[i].getconnectioncount())
        for i in range(4):
            # exp_conns = 2 if i == 0 or i == 3 else 4
            assert_equal(self.nodes[i].getbalance(), starting_balance)
            assert_equal(self.nodes[i].getconnectioncount(), 6)
            # print(i, self.nodes[i].getpeerinfo())
        
        # Fork at height 500
        self.nodes[2].generate(100)
        self.sync_all()
        self.nodes[0].generate(400)
        self.sync_all()
        print('Sending tx')
        # All nodes should still play along until one more block is made
        # However, if we now try to make a tx on either side, its relay will
        # result in a ban for the other network
        tx1 = self.nodes[0].sendtoaddress(self.nodes[1].getnewaddress(), 10)
        tx2 = self.nodes[2].sendtoaddress(self.nodes[3].getnewaddress(), 10)
        # self.sync_all()
        node1seetx1 = False
        for i in range(10):
            # tx1 should only be valid on net 1, so only those nodes should accept it
            try:
                self.nodes[1].getrawtransaction(tx1)
                node1seetx1 = True
                break
            except:
                time.sleep(0.5)
                continue
        assert node1seetx1 and "node 1 did not see tx1"
        node3seetx2 = False
        for i in range(10):
            # tx1 should only be valid on net 1, so only those nodes should accept it
            try:
                self.nodes[3].getrawtransaction(tx2)
                node3seetx2 = True
                break
            except:
                time.sleep(0.5)
                continue
        assert node3seetx2 and "node 3 did not see tx2"
        # # We should now have connections 0-1 and 2-3 but not anywhere else
        # # This results in 1 connection for everyone
        # for i in range(4):
        #     print(i, self.nodes[i].getconnectioncount())
        # for i in range(4):
        #     assert_equal(self.nodes[i].getconnectioncount(), 1)
        # Make another block on either side and wait
        mainblock = self.nodes[0].generate(1)[0]
        forkblock = self.nodes[2].generate(1)[0]
        time.sleep(0.5)
        # Mainies should have main block, forkies should have fork block
        assert_equal(self.nodes[0].getbestblockhash(), mainblock)
        assert_equal(self.nodes[1].getbestblockhash(), mainblock)
        assert_equal(self.nodes[2].getbestblockhash(), forkblock)
        assert_equal(self.nodes[3].getbestblockhash(), forkblock)
        # Txes should have confirmed, but only the once that are valid
        sees = [tx1,tx1,tx2,tx2]
        for i in range(4):
            try:
                self.nodes[i].getrawtransaction(tx1)
            except:
                assert sees[i] != tx1
            try:
                self.nodes[i].getrawtransaction(tx2)
            except:
                assert sees[i] != tx2

if __name__ == '__main__':
    ForkGenTest().main()

