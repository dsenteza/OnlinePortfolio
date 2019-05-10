using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class obstacle : MonoBehaviour {

    //Outlet
    public gameController GameController;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    private void OnCollisionEnter2D(Collision2D collision)
    {
        //GameController.isGameOver = false;
        if(collision.gameObject.GetComponent<blueCircle>())
        {
            Destroy(collision.gameObject);
            GameController.isGameOver = true;
            
        }
        //Lets us know if it's bumped into another player, even another shrek
        print(collision.gameObject.name);
    }

}
