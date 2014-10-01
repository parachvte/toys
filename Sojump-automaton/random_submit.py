#-*- coding: UTF-8 -*-

import httplib
import urllib
import random
import time
from datetime import datetime
from datetime import timedelta


# configure dict for this question
config = {
    "host": "www.sojump.com",
    "curID": "3391294",
}

# common HTTP headers
headers = {
    "Connection": "keep-alive",
    "Cache-Control": "max-age=0",
    "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
    "User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/28.0.1500.95 Safari/537.36",
    "Content-Type": "application/x-www-form-urlencoded",
    "Accept-Encoding": "gzip,deflate,sdch",
    "Accept-Language": "zh-CN,zh;q=0.8",
}


def get_random_data():
    """Random chooses and make a format string.

    Here questions (17, 18, 19) are multi-chooses questions. So the random function here is specified
    and CAN NOT be re-used directlly.

    Expect return example:
        "1$2}2$2}3$2}4$2}5$2}6$3}7$3}8$3}9$3}10$2}11$2}12$3}13$2}14$3}15$3}16$3}17$2|3|4}18$2}19$3}20$3"
    """
    question_num = 20
    res_string = ""
    for q_id in range(1, question_num + 1):
        res_string += str(q_id) + "$"
        if q_id in (1, ):
            chooses = [random.randint(1, 2)]
        elif q_id in (17, 18, 19):
            chooses = sorted(random.sample(range(1, 6), random.randint(1, 5)))
        else:
            chooses = [random.randint(1, 3) + random.randint(0, 2)]  # make a distribution closer to normal distribution
        res_string += "|".join([str(c) for c in chooses]) + "}"
    return res_string


def submit_routine():
    """Submit routine for random answers"""
    conn = httplib.HTTPConnection(config["host"])

    # get cookie
    try:
        conn.request("GET", "/jq/{}.aspx".format(config["curID"]))
    except:
        return False
    res = conn.getresponse()
    if res.getheader("Set-Cookie") is not None:
        headers["Cookie"] = res.getheader("Set-Cookie").split(";")[0]
    res.read()

    # post form
    post_url = "/handler/processjq.ashx?" + urllib.urlencode({
        "submittype": 1,
        "curID": 3391294,
        "t": int(time.time() * 1000),  # current time
        "cp": "广东省",
        "cc": "珠海",
        "ci": "222.16.{}.{}".format(random.randint(1, 255), random.randint(1, 255)),  # 珠海IP附近
        "starttime": (datetime.now() - timedelta(seconds=152)).strftime("%Y/%m/%d %H:%M:%S")
    }).replace("+", "%20")
    print "post_url =", post_url
    data = urllib.urlencode({"submitdata": get_random_data()})
    print "data =", data
    try:
        conn.request("POST", post_url, data, headers)
        res = conn.getresponse()
        with open("result.out", "w") as F:
            F.write(res.read())
    except Exception as e:
        print "Exception"
        return False
    conn.close()
    return True

if __name__ == "__main__":
    for i in range(30):
        if not submit_routine():
            time.sleep(60)  # Maybe IP is blocked, wait for 1 minute and go on
        time.sleep(3)
