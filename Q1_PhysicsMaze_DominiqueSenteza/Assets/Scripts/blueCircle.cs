using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class blueCircle : MonoBehaviour {

    //Outlets
    Rigidbody2D rigidbody;

	// Use this for initialization
	void Start () {
        rigidbody = GetComponent<Rigidbody2D>();
	}
	
	// Update is called once per frame
	void Update () {
		if(Input.GetKey(KeyCode.LeftArrow)) {
            //Rotation default is counterclockwise
            rigidbody.AddTorque(2f);

            //VARIABLES:
            //int wholeNumber = 2;
            //fload decimalNumber = 3f;
            //string word = "hello";
            //bool isAwake = false;

            print("Rotate Left");
        }

        if (Input.GetKey(KeyCode.RightArrow)) {
            rigidbody.AddTorque(-2f);
            print("Rotate Right");
        }

        if (Input.GetKey(KeyCode.Space)) {
            rigidbody.AddRelativeForce(new Vector2(0, 5f));
            print("Thrust");
        }
    }
}
