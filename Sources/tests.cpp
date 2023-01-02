//#include "../Headers/tests.h"
//#include <cassert>
//#include <iostream>
//
//void test_array() {
//    DynamicArray<int> arr;
//    assert(arr.get_size() == 0);
//    arr.add(1);
//    arr.add(2);
//    assert(arr[0] == 1);
//    assert(arr[1] == 2);
//    DynamicArray<int> arr2 = DynamicArray(arr);
//    assert(arr2[0] == 1);
//    assert(arr2[1] == 2);
//
//    arr.clear();
//    assert(arr.get_size() == 0);
//
//    arr = arr2;
//    assert(arr[0] == 1);
//    assert(arr[1] == 2);
//    assert(arr.get_size() == 2);
//    arr.remove(0);
//    assert(arr[0] == 2);
//    assert(arr.get_size() == 1);
//    arr = arr;
//    assert(arr[0] == 2);
//    assert(arr.get_size() == 1);
//}
//
//void test_repo() {
//    Repo r;
//    assert(r.get_size() == 0);
//    assert(r.get_index(1, "1") == -1);
//    assert(r.has(1, "1") == false);
//    assert(r.has(Coat()) == false);
//    r.add(Coat());
//    assert(r.has(Coat()) == true);
//    assert(r.has(0, "") == true);
//    assert(r.get_index(0, "") == 0);
//    assert(r.get_at(0).to_string() == "Size: 0 | Color:  | Price: 0.000000 | Quantity: 0 | Photo: ");
//    r.remove(Coat());
//    assert(r.get_size() == 0);
//
//
//}
//
//void test_coat() {
//    Coat c = Coat();
//    assert(c.get_size() == 0);
//    assert(c.get_price() == 0.0f);
//    assert(c.get_quantity() == 0);
//    assert(c.get_color() == "");
//    assert(c.get_photo() == "");
//
//    Coat c2 = Coat(72, "1222", 1.0f, 1, "1");
//    assert(c2.get_size() == 72);
//    assert(c2.get_price() == 1.0f);
//    assert(c2.get_quantity() == 1);
//    assert(c2.get_color() == "1222");
//    assert(c2.get_photo() == "1");
//
//    assert(Coat::compare_coats(c, c2) == -1);
//    c.update_button_function_too_many_names_aaaaa(72, "1222", 1.0f, 1, "1");
//    assert(c.get_size() == 72);
//    assert(c.get_price() == 1.0f);
//    assert(c.get_quantity() == 1);
//    assert(c.get_color() == "1222");
//    assert(c.get_photo() == "1");
//
//    assert(Coat::compare_coats(c, c2) == 0);
//    assert(c.to_string() == "Size: 72 | Color: 1222 | Price: 1.000000 | Quantity: 1 | Photo: 1");
//
//}
//
//void test_service() {
//    Repo r;
//    Service s = Service(r);
//    assert(s.get_size() == 0);
//    assert(s.get_repo().get_size() == r.get_size());
//    s.add(0, "", 0.0f, 0, "");
//    assert(Coat::compare_coats(s.get_repo().get_at(0), Coat()) == 0);
//    s.update_button_function_too_many_names_aaaaa(0, "", 0.0f, 1, "");
//    assert(Coat::compare_coats(s.get_repo().get_at(0), Coat(0, "", 0.0f, 1, "")) == 0);
//    s.remove(0, "");
//    assert(s.get_size() == 0);
//}
//
//void tests()  {
//    test_array();
//    test_coat();
//    test_repo();
//    test_service();
//}